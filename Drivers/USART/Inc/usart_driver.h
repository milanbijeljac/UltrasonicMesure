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
			init();
		}

		void disable_clock();

		/* Blocking for now */
		uint8 read_byte(void);
		void  read_message(uint8* data, uint8 size);
		void  write_byte(uint8 data);
		void  write_message(uint8* data, uint8 size);

		/* Construct-once, live-forever peripheral object: trivial destructor
		 * (no static-destructor/atexit overhead). Non-copyable/non-movable so
		 * two objects can never alias or re-init the same peripheral. */
		~USART() = default;

		USART(const USART&)            = delete;

		USART& operator=(const USART&) = delete;

		USART(USART&&)                 = delete;

		USART& operator=(USART&&)      = delete;

	private:
		void init();
		void enable_clock();
	private:
		USART_TypeDef* m_USARTx {nullptr};
		uint32 m_clock {0};
		uint32 m_baudRate {0};
	};
}
