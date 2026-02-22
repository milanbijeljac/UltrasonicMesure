#pragma once

#include <stm32f072x8.h>
#include "types.h"

namespace Driver
{
	/** Base timer class */
	class TIM
	{
	public:
		explicit TIM(TIM_TypeDef* TIMx, uint8 frequency ) : m_TIMx(TIMx), m_frequency(frequency)
		{

		}

	public:
		void TIM_v_Init();
		void Delay_v_us (uint16 us);
		void Delay_v_ms (uint16 ms);
		~TIM() = default;

	private:
		void TIM_v_EnableClock();

	protected:
		TIM_TypeDef* m_TIMx;

	private:
		uint8 m_frequency;   /** Frequency in MHz */


	};

	/** General purpose timers */
	class GP_TIM : public TIM
	{
	public:
		GP_TIM(TIM_TypeDef* TIMx, uint8 frequency ) : TIM(TIMx, frequency)
		{

		}

		GP_TIM(TIM_TypeDef* TIMx, uint8 frequency, uint32 autoReloadValue ) : TIM(TIMx, frequency), m_autoReloadValue(autoReloadValue)
		{

		}

		void GP_TIM_v_Init();
		void GP_TIM_v_InputCaptureModeConfig();
		void GP_TIM_v_InputCaptureModeIRQHandling();
		uint32 GP_TIM_u_GetCaptureValue () const { return m_captureDifference; };
		~GP_TIM() = default;

	private:
		uint32 m_autoReloadValue = 0;
		uint32 m_captureDifference;
		uint32 m_inputCapture1;
		uint32 m_inputCapture2;
	};
}

