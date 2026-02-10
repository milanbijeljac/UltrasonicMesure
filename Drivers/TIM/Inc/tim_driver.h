#pragma once

#include <stm32f072x8.h>
#include "types.h"

namespace Driver
{
	class TIM {
	public:
		TIM(TIM_TypeDef* TIMx,
			uint8 frequency )
		: m_TIMx(TIMx),
		  m_frequency(frequency)
		{
			TIM_v_Init();
		}

	public:
		void Delay_v_us (uint16 us);
		void Delay_v_ms (uint16 ms);

	private:
		void TIM_v_Init();

	private:
		TIM_TypeDef* m_TIMx;
		uint8 m_frequency;
	};
}
