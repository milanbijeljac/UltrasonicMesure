# UltrasonicMesure

Bare-metal firmware for the **STM32F072RB** (ARM Cortex-M0) that measures distance
with an **HC-SR04** ultrasonic sensor. All peripheral access is done through hand-written,
register-level C++ drivers — no vendor HAL/LL libraries. On top of the drivers sits a
small **hardware-abstraction layer (HAL)** of pure-virtual interfaces, so the sensor
logic is portable and unit-testable off-target. Built with **STM32CubeIDE**
(Eclipse-based managed makefile build).

## Hardware

| Item        | Value                                             |
|-------------|---------------------------------------------------|
| MCU         | STM32F072RBTx (Cortex-M0, 128 KB flash, 16 KB RAM) |
| Board       | STM32 Nucleo-64 (F072RB) / compatible             |
| Sensor      | HC-SR04 ultrasonic ranging module                 |
| System clock| HSI (8 MHz) → PLL ×4 = **16 MHz**                  |

### Pin map

| Signal            | Port / Pin | Mode                     | Notes                         |
|-------------------|-----------|--------------------------|-------------------------------|
| USART2 TX         | PA2       | Alternate function AF1   | Serial debug / data out       |
| USART2 RX         | PA3       | Alternate function AF1   |                               |
| TIM2 CH1/ETR      | PA0       | Alternate function AF2   | Input capture (echo timing)   |
| Sensor Trigger    | PC8       | Output, push-pull        | Drives HC-SR04 `TRIG`         |

> The current test wiring connects **PC8 (trigger)** to **PA0 (TIM2 input capture)**
> so the echo pulse can be timed on the same board. Wire PA0 to the sensor's `ECHO`
> pin (with appropriate level shifting — ECHO is 5 V) for real measurements.

## Architecture

The code is layered so the sensor logic never touches a register:

```
  Application / device       Sensor::HCSR04   (holds hal::I* references)
          │ depends on
          ▼
  HAL interfaces  (hal/)      IDigitalOutput   ICaptureTimer   IDelay
          ▲ implemented by                         (pure virtual, portable)
          │
  Platform adapters           platform::stm32::GpioOutput / CaptureTimer / Delay
  (platform/stm32f072/)        └─ wrap Driver::GPIO / GP_TIM / TIM
  register-level drivers      Driver::GPIO   Driver::GP_TIM   Driver::USART
  (Drivers/)                   └─ touch the CMSIS registers directly
```

`HCSR04` and everything in `hal/` contain **zero** STM32 types. The concrete hardware
is named in exactly one place — the composition root in `main.cpp` — which constructs
the `platform::stm32` adapters and injects them into the sensor by reference. Porting
to another MCU means writing a new `platform/<mcu>/` and editing only that wiring file.
The HAL exposes **meaningful units** (a pulse width in microseconds, a logical pin
state) rather than ticks or register values.

## How it works

1. **Clock setup** — `PLL_Enable()` in `main.cpp` brings up HSI, configures the PLL
   (×4) and switches the system clock to 16 MHz.
2. **Composition root** — `main` builds the register-level drivers (`Driver::GPIO`,
   `Driver::GP_TIM timer2`, `Driver::TIM timer6`), wraps them in the `platform::stm32`
   adapters, and injects those into `Sensor::HCSR04`.
3. **`HCSR04::measure()`** runs one ranging cycle through the interfaces:
   - `trig.set()` → `delay.us(10)` → `trig.clear()` emits the ≥10 µs trigger pulse.
   - the sensor's echo pin drives PA0; **TIM2** input-capture records the rising
     (CC1) and falling (CC2) edges, and `TIM2_IRQHandler` stores the pulse width.
   - after the echo window, `echo.last_pulse_width_us()` returns the width **in
     microseconds** (the adapter converts timer ticks → µs using the timer frequency).
4. **Distance** — `HCSR04::to_distance(us, unit)` converts microseconds to distance:
   - centimeters: `us / 58.0`
   - inches: `us / 148.0`

   Because the interface speaks microseconds, this math is independent of the timer
   prescaler; the tick→µs conversion lives entirely in the STM32 adapter.

## Project layout

```
Src/                     Application entry point (main.cpp = composition root) + syscalls/sysmem
Inc/                     MCU headers (stm32f072x8.h) and common types (types.h)
Drivers/
  GPIO/                  GPIO class + inline GpioHelper read/write/toggle helpers
  TIM/                   TIM base class + GP_TIM (general-purpose timer, input capture)
  USART/                 USART class (blocking byte/message read & write)
hal/Inc/                 Portable interfaces: IDigitalOutput, ICaptureTimer, IDelay
platform/
  stm32f072/             STM32 adapters implementing the hal interfaces over Driver::*
  host/Inc/              Test fakes (FakeDigitalOutput/CaptureTimer/Delay) — off-target only
CMSIS/                   ARM CMSIS Cortex-M0 core headers
DataStructure/
  RingBuffer/            Templated ring buffer (placement-new, Status-returning ops)
Sensor/
  sensor_base.{h,cpp}    SensorBase (holds sensor name; protected non-virtual dtor)
  HC-SR04/               HCSR04 device driver — depends on the hal interfaces
Startup/                 startup_stm32f072rbtx.s
Debug/                   Generated build output (STM32CubeIDE)
STM32F072RBTX_FLASH.ld   Linker script
```

## Component overview

- **`hal::IDigitalOutput` / `ICaptureTimer` / `IDelay`** — pure-virtual capabilities the
  sensor needs: a trigger line, an echo-width timer (in µs), and a blocking delay.
- **`platform::stm32::GpioOutput` / `CaptureTimer` / `Delay`** — implement the interfaces
  by delegating to the register drivers; `CaptureTimer` also converts ticks → µs.
- **`platform::host::Fake*`** — in-memory implementations for PC unit tests (inject a
  canned pulse width, assert the resulting distance) without any hardware.
- **`Sensor::HCSR04`** — device driver holding `hal::I*` references; `measure(Unit)` runs
  the trigger/echo sequence, `to_distance()` is the pure (testable) µs→distance math.
- **`Driver::GPIO` / `GpioHelper`** — pin config on construction; inline read/write/
  toggle and BSRR set/reset helpers. Non-copyable/non-movable (owns a peripheral).
- **`Driver::TIM` / `GP_TIM`** — base timer with `delay_us/ms`; `GP_TIM` adds
  input-capture config and IRQ handling for pulse-width measurement.
- **`Driver::USART`** — blocking 8N1 serial (byte/message read/write), 115200 baud.
- **`DataStructure::RingBuffer<T>`** — fixed-size ring buffer via `create_obj()`
  (placement new, stack or heap); `write_element`/`read_element` return a `Status`.

## Building & flashing

1. Import the project into **STM32CubeIDE** (`File → Import → Existing Projects`).
2. Build the `Debug` configuration (`Project → Build`).
   - New source folders (`hal`, `platform`, `Sensor`, …) and their include paths are
     registered in `.cproject`; run **Project → Clean** first if you add more.
3. Flash/debug over ST-Link with the provided `UltrasonicMesure.launch` /
   `UltrasonicMesure.cfg` (OpenOCD) configuration.

Semihosting is enabled (`initialise_monitor_handles()`), so `printf`-style output and
the computed `distance` can be observed in the debugger console.

## Status & notes

Work-in-progress learning/bring-up project. Current limitations:

- The input-capture path supports a single channel pairing (rising on CC1, falling on
  CC2) — see the `TODO` in `GP_TIM::input_capture_mode_config()`.
- `CaptureTimer::start()` is currently a no-op (the interrupt-driven timer keeps the
  last captured value); revisit if a re-arm is needed per measurement.
- USART and delay routines are **blocking**.
- `measure()` uses a fixed post-trigger delay as the echo window rather than waiting on
  a capture-complete flag.
- The computed `distance` is not yet transmitted over USART (the serial send block is
  compiled out with `#if(0)`).
- Host unit tests using `platform/host` fakes are scaffolded but not yet built.
