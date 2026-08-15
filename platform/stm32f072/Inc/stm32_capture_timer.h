#pragma once

#include "i_capture_timer.h"
#include "tim_driver.h"

namespace platform::stm32
{
	/**
	 * ICaptureTimer backed by a Driver::GP_TIM running in input-capture mode.
	 * Converts the raw captured tick count into microseconds using the timer's
	 * counter frequency, so the sensor driver never sees ticks or prescalers.
	 */
	class CaptureTimer final : public hal::ICaptureTimer
	{
	public:
		/**
		 * @param timer     GP_TIM already initialised in input-capture mode.
		 * @param timer_hz  Counter frequency in Hz (ticks per second), e.g.
		 *                  1'000'000 for a 1 us tick.
		 */
		CaptureTimer(Driver::GP_TIM& timer, uint32 timer_hz) noexcept
			: m_timer(timer), m_timer_hz(timer_hz)
		{
		}

		void start() noexcept override;
		[[nodiscard]] uint32 last_pulse_width_us() const noexcept override;

	private:
		Driver::GP_TIM& m_timer;
		uint32          m_timer_hz;
	};
}
