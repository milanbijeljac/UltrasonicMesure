#pragma once


#include <stm32f072x8.h>
#include "types.h"

namespace Driver
{
	class USART
	{

	public:

		USART(USART_TypeDef* UARTx,
			uint32 clock,
			uint32 baudRate)
		: m_USARTx(UARTx),
		  m_clock(clock),
		  m_baudRate(baudRate)
		{
			USART_v_Init();
		}

		void USART_v_DisableClock();

		/* Blocking for now */
		uint8 UART_ReadByte(void);
		void  USART_v_ReadMessage(uint8* data, uint8 size);
		void  USART_v_WriteByte(uint8 data);
		void  USART_v_WriteMessage(uint8* data, uint8 size);

		/* Construct-once, live-forever peripheral object: trivial destructor
		 * (no static-destructor/atexit overhead). Non-copyable/non-movable so
		 * two objects can never alias or re-init the same peripheral. */
		~USART() = default;

		USART(const USART&)            = delete;

		USART& operator=(const USART&) = delete;

		USART(USART&&)                 = delete;

		USART& operator=(USART&&)      = delete;

	private:
		void USART_v_Init();
		void USART_v_EnableClock();
	private:
		USART_TypeDef* m_USARTx {nullptr};
		uint32 m_clock {0};
		uint32 m_baudRate {0};
	};
}
