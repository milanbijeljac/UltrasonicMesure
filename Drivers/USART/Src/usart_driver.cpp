#include "usart_driver.h"
#include "stm32f072x8.h"

namespace Driver
{
	void USART::USART_v_Init()
	{
		USART::USART_v_EnableClock();

	    /* Disable USART */
		USART::m_USARTx->CR1 &= ~USART_CR1_UE;

	    /* Baud rate */
		USART::m_USARTx->BRR = USART::m_clock / USART::m_baudRate;

	    /* 8 data bits, no parity */
		USART::m_USARTx->CR1 &= ~(USART_CR1_M | USART_CR1_PCE);

	    /* 1 stop bit */
		USART::m_USARTx->CR2 &= ~USART_CR2_STOP;

	    /* Enable TX and RX */
		USART::m_USARTx->CR1 |= USART_CR1_TE | USART_CR1_RE;

	    /* Enable USART */
		USART::m_USARTx->CR1 |= USART_CR1_UE;
	}

	uint8 USART::UART_ReadByte(void)
	{
		while (!(m_USARTx->ISR & USART_ISR_RXNE));
		return (uint8)m_USARTx->RDR;
	}

	void USART::USART_v_ReadMessage(uint8* data, uint8 size)
	{
	    uint8 i;

	    for (i = 0; i < size; i++)
	    {
	        while (!(m_USARTx->ISR & USART_ISR_RXNE));
	        data[i] = (uint8)m_USARTx->RDR;
	    }
	}

	void USART::USART_v_WriteByte(uint8 data)
	{
	    while (!(m_USARTx->ISR & USART_ISR_TXE));
	    m_USARTx->TDR = data;
	}

	void USART::USART_v_WriteMessage(uint8* data, uint8 size)
	{
	    uint8 i;

	    for (i = 0; i < size; i++)
	    {
	        while (!(m_USARTx->ISR & USART_ISR_TXE));
	        m_USARTx->TDR = data[i];
	    }
	}

	void USART::USART_v_EnableClock()
	{
		if(USART::m_USARTx == USART1) { (RCC->APB2ENR |= (1u << 14u));  }
		if(USART::m_USARTx == USART2) { (RCC->APB1ENR |= (1u << 17u));  }
		if(USART::m_USARTx == USART3) { (RCC->APB1ENR |= (1u << 18u));  }
		if(USART::m_USARTx == USART4) { (RCC->APB1ENR |= (1u << 19u));  }
	}

	void USART::USART_v_DisableClock()
	{
		if(USART::m_USARTx == USART1) { (RCC->APB2ENR &= ~(1u << 14u));  }
		if(USART::m_USARTx == USART2) { (RCC->APB1ENR &= ~(1u << 17u));  }
		if(USART::m_USARTx == USART3) { (RCC->APB1ENR &= ~(1u << 18u));  }
		if(USART::m_USARTx == USART4) { (RCC->APB1ENR &= ~(1u << 19u));  }
	}
}
