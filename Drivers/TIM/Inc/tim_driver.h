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
		void init();
		void delay_us (uint16 us);
		void delay_ms (uint16 ms);
		/* Construct-once, live-forever peripheral object: trivial destructor
		 * (no static-destructor/atexit overhead). Non-copyable/non-movable so
		 * two objects can never alias or re-init the same peripheral. */
		~TIM() = default;

		TIM(const TIM&)            = delete;

		TIM& operator=(const TIM&) = delete;

		TIM(TIM&&)                 = delete;

		TIM& operator=(TIM&&)      = delete;

	private:
		void enable_clock();

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

		void init();
		void input_capture_mode_config();
		void input_capture_mode_irq_handling();
		[[nodiscard]] uint32 get_capture_value () const noexcept { return m_captureDifference; };
		~GP_TIM() = default;

		/* Prevent accidental copies that would re-init same peripheral */
		GP_TIM(const GP_TIM&)            = delete;

		GP_TIM& operator=(const GP_TIM&) = delete;

		GP_TIM(GP_TIM&&)                 = delete;

		GP_TIM& operator=(GP_TIM&&)      = delete;

	private:
		uint32 m_autoReloadValue = 0;
		volatile uint32 m_captureDifference = {0};
		uint32 m_inputCapture1 = {0};
		uint32 m_inputCapture2 = {0};
	};
}

