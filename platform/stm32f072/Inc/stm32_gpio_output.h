#pragma once

#include "i_digital_output.h"
#include "gpio_driver.h"

namespace platform::stm32
{
	/** IDigitalOutput backed by an already-configured Driver::GPIO output pin. */
	class GpioOutput final : public hal::IDigitalOutput
	{
	public:
		GpioOutput(GPIO_TypeDef* port, Driver::GPIO::GpioPin pin) noexcept
			: m_port(port), m_pin(pin)
		{
		}

		void set()   noexcept override;
		void clear() noexcept override;

	private:
		GPIO_TypeDef*         m_port;
		Driver::GPIO::GpioPin m_pin;
	};
}
