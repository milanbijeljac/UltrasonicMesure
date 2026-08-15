#pragma once

#include "i_delay.h"
#include "tim_driver.h"

namespace platform::stm32
{
	/** IDelay backed by a Driver::TIM used for busy-wait delays. */
	class Delay final : public hal::IDelay
	{
	public:
		explicit Delay(Driver::TIM& timer) noexcept : m_timer(timer)
		{
		}

		void us(uint16 microseconds) noexcept override;
		void ms(uint16 milliseconds) noexcept override;

	private:
		Driver::TIM& m_timer;
	};
}
