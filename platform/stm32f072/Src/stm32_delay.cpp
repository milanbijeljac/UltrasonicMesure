#include "stm32_delay.h"

namespace platform::stm32
{
	void Delay::us(uint16 microseconds) noexcept
	{
		m_timer.delay_us(microseconds);
	}

	void Delay::ms(uint16 milliseconds) noexcept
	{
		m_timer.delay_ms(milliseconds);
	}
}
