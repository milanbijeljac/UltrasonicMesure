#include "tim_driver.h"

#define US_TO_MS 1000u
#define MS_TO_S  1000u

namespace Driver
{
	void TIM::TIM_v_Init()
	{
		TIM::TIM_v_EnableClock();

		/* APB bus clock speed is currently set at value provided as argument
		 * frequency (-1 since PSC register is configured that way)             */
		m_TIMx->PSC = TIM::m_frequency - 1u;
		m_TIMx->ARR = 0xFFFFu;
		m_TIMx->CR1 |= 1u << 0u;
		while(!(m_TIMx->SR & (1u << 0u)));
	}

	void TIM::TIM_v_EnableClock()
	{
		if(m_TIMx == TIM1 ) { RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  }
		if(m_TIMx == TIM2 ) { RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  }
		if(m_TIMx == TIM3 ) { RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;  }
		if(m_TIMx == TIM6 ) { RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;  }
		if(m_TIMx == TIM7 ) { RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;  }
		if(m_TIMx == TIM14) { RCC->APB1ENR |= RCC_APB1ENR_TIM14EN; }
		if(m_TIMx == TIM15) { RCC->APB2ENR |= RCC_APB2ENR_TIM15EN; }
		if(m_TIMx == TIM16) { RCC->APB2ENR |= RCC_APB2ENR_TIM16EN; }
		if(m_TIMx == TIM17) { RCC->APB2ENR |= RCC_APB2ENR_TIM17EN; }


	};

	void TIM::Delay_v_us (uint16 us)
	{
		m_TIMx->CNT = 0u;
		while (m_TIMx->CNT < us);

	}
	void TIM::Delay_v_ms (uint16 ms)
	{
		for (uint16 i = 0; i < ms; i++)
		{
			Delay_v_us(US_TO_MS);
		}
	}
}



