#pragma once

#include "types.h"
#include "stm32f072x8.h"

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

		~USART() = default;

	private:
		void USART_v_Init();
		void USART_v_EnableClock();
	private:
		USART_TypeDef* m_USARTx;
		uint32 m_clock;
		uint32 m_baudRate;
	};
}
