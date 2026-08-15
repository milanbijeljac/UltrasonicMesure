#pragma once

#include "i_capture_timer.h"

namespace platform::host
{
	/** ICaptureTimer test double: returns a pulse width you set from the test. */
	class FakeCaptureTimer final : public hal::ICaptureTimer
	{
	public:
		void start() noexcept override { ++m_start_count; }

		[[nodiscard]] uint32 last_pulse_width_us() const noexcept override
		{
			return m_pulse_width_us;
		}

		/** Test hook: stage the value the next read should return. */
		void set_pulse_width_us(uint32 us) noexcept { m_pulse_width_us = us; }
		[[nodiscard]] unsigned start_count() const noexcept { return m_start_count; }

	private:
		uint32   m_pulse_width_us{0};
		unsigned m_start_count{0};
	};
}
