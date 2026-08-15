#pragma once

#include "types.h"

namespace hal
{
	/** Abstract blocking delay source. */
	class IDelay
	{
	public:
		virtual void us(uint16 microseconds) noexcept = 0;
		virtual void ms(uint16 milliseconds) noexcept = 0;

	protected:
		~IDelay() = default;
	};
}
