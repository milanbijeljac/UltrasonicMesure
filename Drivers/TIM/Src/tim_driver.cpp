#include "tim_driver.h"

#define US_TO_MS 1000u
#define MS_TO_S  1000u

namespace Driver
{
	void TIM::TIM_v_Init()
	{
		RCC->APB1ENR |= 1u << 1u; /* Currently only TIM3 */

		RCC->CFGR |= 3u << 0u;

		/* APB bus clock speed is currently set at value provided as argument
		 * frequency (-1 since PSC register is configured that way)             */
		TIM3->PSC = TIM::m_frequency - 1u;
		TIM3->ARR = 0xFFFFu;
		TIM3->CR1 |= 1u << 0u;
		while(!(TIM3->SR & (1u << 0u)));
	}

	void TIM::Delay_v_us (uint16 us)
	{
		TIM3->CNT = 0u;
		while (TIM3->CNT < us);

	}
	void TIM::Delay_v_ms (uint16 ms)
	{
		for (uint16 i = 0; i < ms; i++)
		{
			Delay_v_us(US_TO_MS);
		}
	}
}



