#include "stm32_capture_timer.h"

namespace platform::stm32
{
	void CaptureTimer::start() noexcept
	{
		/* TODO(3.3): if a measurement needs the capture (re)armed each time,
		 * do it here. With the current interrupt-driven GP_TIM the last value
		 * is simply kept in the driver, so this may stay empty. Decide together. */
	}

	uint32 CaptureTimer::last_pulse_width_us() const noexcept
	{
		const uint32 ticks = m_timer.get_capture_value();

		if (m_timer_hz == 0u)
		{
			return 0u;
		}

		/* us = ticks * 1e6 / timer_hz. 64-bit intermediate to avoid overflow;
		 * for a 1 MHz timer this collapses to `ticks`. */
		return static_cast<uint32>((static_cast<uint64>(ticks) * 1000000u) / m_timer_hz);
	}
}
