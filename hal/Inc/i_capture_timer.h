#pragma once

#include "types.h"

namespace hal
{
	/**
	 * Abstract input-capture timer used to measure an echo pulse width.
	 * Exposes the result in MICROSECONDS so callers stay free of timer-tick /
	 * prescaler details (that conversion lives in the platform implementation).
	 */
	class ICaptureTimer
	{
	public:
		/** Arm / reset the timer before starting a new measurement. */
		virtual void start() noexcept = 0;

		/** Width of the most recently captured pulse, in microseconds. */
		[[nodiscard]] virtual uint32 last_pulse_width_us() const noexcept = 0;

	protected:
		~ICaptureTimer() = default;
	};
}
