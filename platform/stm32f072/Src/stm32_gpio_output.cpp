#include "stm32_gpio_output.h"

namespace platform::stm32
{
	void GpioOutput::set() noexcept
	{
		Driver::GpioHelper::bit_set_reset_config(m_port, m_pin, SET);
	}

	void GpioOutput::clear() noexcept
	{
		Driver::GpioHelper::bit_set_reset_config(m_port, m_pin, RESET);
	}
}
