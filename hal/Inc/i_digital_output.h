#pragma once

namespace hal
{
	/**
	 * Abstract single digital output line (e.g. an ultrasonic sensor TRIG pin).
	 * A device driver depends on this instead of a concrete GPIO, so it can be
	 * built against real hardware or a test fake.
	 */
	class IDigitalOutput
	{
	public:
		virtual void set()   noexcept = 0;   /* drive the line high */
		virtual void clear() noexcept = 0;   /* drive the line low  */

	protected:
		/* Non-virtual + protected: implementations are owned/destroyed by the
		 * concrete type, never deleted through an IDigitalOutput*. No vtable
		 * slot spent on the destructor. */
		~IDigitalOutput() = default;
	};
}
