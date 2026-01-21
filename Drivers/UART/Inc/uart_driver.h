#pragma once


namespace Driver
{
	class UART
	{
	public:

		~UART() = default;
	private:
		USART_TypeDef* m_UARTx;
	};
}
