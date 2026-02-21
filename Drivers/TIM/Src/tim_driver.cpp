#include "tim_driver.h"
#include <core_cm0.h>

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

	void GP_TIM::GP_TIM_v_Init()
	{
		TIM::TIM_v_Init();
		if(m_autoReloadValue != 0)
		{
			m_TIMx->CR1 &= ~TIM_CR1_CEN;         /* Disable timer */
			m_TIMx->ARR = m_autoReloadValue;
			m_TIMx->CR1 |= TIM_CR1_CEN;         /* Start timer */
		}
	}

	void GP_TIM::GP_TIM_v_InputCaptureModeConfig()
	{
		/* For now capture/compare channels 1 and 2 are mapped to timer input 1, where rising edge was used for CC1 and falling for CC2 */
		/* TODO: Expand driver to have multiple selection */

		m_TIMx->CR1 &= ~TIM_CR1_CEN;         /* Disable timer */

		m_TIMx->CCMR1 |= TIM_CCMR1_CC1S_0;  /* CC1 mapped to TI1 */
		m_TIMx->CCMR1 |= TIM_CCMR1_CC2S_1;  /* CC2 mapped to TI1 */
		m_TIMx->CCER &= ~TIM_CCER_CC1P;     /* Rising edge for CC1 */
		m_TIMx->CCER |= TIM_CCER_CC2P;      /* Falling edge for CC2 */
		m_TIMx->CCER |= TIM_CCER_CC1E;      /* Enable capture for CC1 */
		m_TIMx->CCER |= TIM_CCER_CC2E;      /* Enable capture for CC2 */

		m_TIMx->DIER |= TIM_DIER_CC1IE;     /* Enable interrupt for CC1 */
		m_TIMx->DIER |= TIM_DIER_CC2IE;     /* Enable interrupt for CC1 */

		NVIC_EnableIRQ(TIM2_IRQn);

		m_TIMx->CR1 |= TIM_CR1_CEN;         /* Start timer */
	}

	void GP_TIM::GP_TIM_v_InputCaptureModeIRQHandling()
	{
		uint8 step;
	    if (m_TIMx->SR & TIM_SR_CC1IF)
	    {
	    	m_inputCapture1 = m_TIMx->CCR1; /* TIM_SR_CC1IF flag cleared when by reading TIMx_CCR1 register */
	    	step = 1;
	    }
	    else if(m_TIMx->SR & TIM_SR_CC2IF)
	    {
	    	m_inputCapture2 = m_TIMx->CCR2; /* TIM_SR_CC2IF flag cleared when by reading TIMx_CCR2 register */
	    	step = 2;
	    }

	    if(step == 2)
	    {
	    	if(m_inputCapture2 < m_inputCapture1)
	    	{
	    		/* In case of overflow calculate what value that overflowed (capture1) and add
	    		 * current setting of ARR minus what was left from capture2) */
	    		m_captureDifference = m_inputCapture2 + (m_TIMx->ARR - m_inputCapture1);
	    		m_captureDifference /= 58;
	    	}
	    	else
			{
	    		m_captureDifference = m_inputCapture2 - m_inputCapture1;
	    		m_captureDifference /= 58;
			}
	    }
	}
}



