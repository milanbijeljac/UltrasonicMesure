#include <math.h>
#include "gpio_driver.h"
#include "stm32f072x8.h"
#include "types.h"

/* Macros used for clearing bit fields */
#define CLEAR_1_BIT					1u
#define CLEAR_2_BITS 				3u
#define CLEAR_4_BITS				4u

/** Macro that is used for separation of low and high pins */
#define PIN_SEPARATION				7u

namespace Driver
{

	void GPIO::GPIO_v_Init()
	{
		GPIO::GPIO_v_ModerConfig();
		GPIO::GPIO_v_SpeedConfig();
		GPIO::GPIO_v_PupdrConfig();
		GPIO::GPIO_v_OutputConfig();
		if(m_Moder == GPIO::Mode::AlternateFunctionMode)
		{
			GPIO::GPIO_v_AlternateFunctionConfig();
		}
	}

	void GPIO::GPIO_v_DeInit()
	{
		if(m_port == GPIOA)
		{
			/* Reset GPIOA peripheral, bit position 17 at RCC_AHBSTR register */
			RCC->AHBRSTR |= 1u << 17u;
			RCC->AHBRSTR &= ~(1u << 17u);
		}
		else if(m_port == GPIOB)
		{
			/* Reset GPIOB peripheral, bit position 18 at RCC_AHBSTR register */
			RCC->AHBRSTR |= 1u << 18u;
			RCC->AHBRSTR &= ~(1u << 18u);
		}
		else if(m_port == GPIOC)
		{
			/* Reset GPIOC peripheral, bit position 19 at RCC_AHBSTR register */
			RCC->AHBRSTR |= 1u << 19u;
			RCC->AHBRSTR &= ~(1u << 19u);
		}
		else if(m_port == GPIOD)
		{
			/* Reset GPIOD peripheral, bit position 20 at RCC_AHBSTR register */
			RCC->AHBRSTR |= 1u << 20u;
			RCC->AHBRSTR &= ~(1u << 20u);
		}
		else if(m_port == GPIOE)
		{
			/* Reset GPIOE peripheral, bit position 21 at RCC_AHBSTR register */
			RCC->AHBRSTR |= 1u << 21u;
			RCC->AHBRSTR &= ~(1u << 21u);
		}
		else if(m_port == GPIOF)
		{
			/* Reset GPIOF peripheral, bit position 22 at RCC_AHBSTR register */
			RCC->AHBRSTR |= 1u << 22u;
			RCC->AHBRSTR &= ~(1u << 22u);
		}
		else
		{
			/* Do nothing */
		}
	}

	void GPIO::GPIO_v_ModerConfig()
	{
		uint8 u_port;
		uint8 u_extiBitShift;
		float extiToPinMap;

		/* Perform clear bit operation */
		m_port->MODER &= ~(CLEAR_2_BITS << (static_cast<uint8>(m_GpioPin) * 2));

		if(static_cast<uint8>(m_Moder) <= static_cast<uint8>(GPIO::Mode::AnalogMode))
		{
			/* Non interrupt mode */
			m_port->MODER |= static_cast<uint8>(m_Moder) << (static_cast<uint8>(m_GpioPin) * 2);
		}
		else if( (static_cast<uint8>(m_Moder) > static_cast<uint8>(GPIO::Mode::AnalogMode)) && (static_cast<uint8>(m_Moder) <= static_cast<uint8>(GPIO::Mode::IRQ_RisingFallingTrigger)) )
		{
			/* Interrupt mode */
			if(static_cast<uint8>(m_Moder) == static_cast<uint8>(GPIO::Mode::IRQ_FallingTrigger))
			{
				/* Clear rising trigger */
				EXTI->RTSR &= ~(1u << static_cast<uint8>(m_GpioPin));

				EXTI->FTSR |= (1u << static_cast<uint8>(m_GpioPin));
			}
			else if(static_cast<uint8>(m_Moder) == static_cast<uint8>(GPIO::Mode::IRQ_RisingTrigger))
			{
				/* Clear falling trigger */
				EXTI->FTSR &= ~(1u << static_cast<uint8>(m_GpioPin));

				EXTI->RTSR |= (1u << static_cast<uint8>(m_GpioPin));
			}
			else /* Rising falling trigger */
			{
				EXTI->FTSR |= (1u << static_cast<uint8>(m_GpioPin));

				EXTI->RTSR |= (1u << static_cast<uint8>(m_GpioPin));
			}

			/* Configure GPIO port selection in SYSCFG_EXTICR
			 * For different ports, different values need to be stored in register*/
			u_port = GPIO::GPIO_u_PortCheck();

			/* Check in which of 4 EXTI registers PIN belong */
			extiToPinMap = static_cast<uint8>(m_GpioPin) / 4u;

			/* Determine start position of PIN in register */
			u_extiBitShift = static_cast<uint8>(m_GpioPin) % 4u;

			SYSCFG_PLCK_EN();

			extiToPinMap = (uint8)floor((double)extiToPinMap);

			SYSCFG->EXTICR[(uint8)extiToPinMap] = u_port << (u_extiBitShift * 4u);

			/* Enable the EXTI interrupt delivery using Interrupt Mask Register */
			EXTI->IMR |= (1 << static_cast<uint8>(m_GpioPin));
		}

	}

	void GPIO::GPIO_v_SpeedConfig()
	{
		/* Perform clear bit operation */
		m_port->OSPEEDR &= ~(CLEAR_2_BITS << (static_cast<uint8>(m_GpioPin) * 2));
		m_port->OSPEEDR |= static_cast<uint8>(m_Speed) << (static_cast<uint8>(m_GpioPin) * 2);
	}

	void GPIO::GPIO_v_PupdrConfig()
	{
		/* Perform clear bit operation */
		m_port->PUPDR &= ~(CLEAR_2_BITS << (static_cast<uint8>(m_GpioPin)* 2));
		m_port->PUPDR |= static_cast<uint8>(m_PullUpDown) << (static_cast<uint8>(m_GpioPin)* 2);
	}

	void GPIO::GPIO_v_OutputConfig()
	{
		/* Perform clear bit operation */
		m_port->OTYPER &= ~(CLEAR_1_BIT << (static_cast<uint8>(m_GpioPin) * 2));
		m_port->OTYPER |= static_cast<uint8>(m_OutputType) << static_cast<uint8>(m_GpioPin);
	}

	void GPIO::GPIO_v_AlternateFunctionConfig()
	{
		if(static_cast<uint8>(m_GpioPin) <= PIN_SEPARATION)
		{
			/* Perform clear bit operation */
			m_port->AFR[0] &= ~(CLEAR_4_BITS << (static_cast<uint8>(m_GpioPin) * 2));
			m_port->AFR[0] |= static_cast<uint8>(m_AlternateFunctionality) << (static_cast<uint8>(m_GpioPin) * 4);

		}
		else if(static_cast<uint8>(m_GpioPin) > PIN_SEPARATION)
		{
			/* Perform clear bit operation */
			m_port->AFR[1] &= ~(CLEAR_4_BITS << (static_cast<uint8>(m_GpioPin) * 2));
			m_port->AFR[1] |= static_cast<uint8>(m_AlternateFunctionality) << ((static_cast<uint8>(m_GpioPin) - 8u) * 4);
		}
	}

	uint8 GPIO::GPIO_u_PortCheck()
	{
		uint8 u_retVal = 0u;

		if(m_port == GPIOA) u_retVal = 0;
		if(m_port == GPIOB) u_retVal = 1;
		if(m_port == GPIOC) u_retVal = 2;
		if(m_port == GPIOD) u_retVal = 3;
		if(m_port == GPIOE) u_retVal = 4;
		if(m_port == GPIOF) u_retVal = 5;

		return u_retVal;
	}

	void GPIO::GPIO_v_RCCEnable()
	{
		if(this->m_port == GPIOA) { (RCC->AHBENR |= (1u << 17u)); }
		if(this->m_port == GPIOB) { (RCC->AHBENR |= (1u << 18u)); }
		if(this->m_port == GPIOC) { (RCC->AHBENR |= (1u << 19u)); }
		if(this->m_port == GPIOD) { (RCC->AHBENR |= (1u << 20u)); }
		if(this->m_port == GPIOE) { (RCC->AHBENR |= (1u << 21u)); }
		if(this->m_port == GPIOF) { (RCC->AHBENR |= (1u << 22u)); }
	};

	void GPIO::GPIO_v_RCCDisable()
	{
		if(this->m_port == GPIOA) { (RCC->AHBENR &= ~(1u << 17u)); }
		if(this->m_port == GPIOB) { (RCC->AHBENR &= ~(1u << 18u)); }
		if(this->m_port == GPIOC) { (RCC->AHBENR &= ~(1u << 19u)); }
		if(this->m_port == GPIOD) { (RCC->AHBENR &= ~(1u << 20u)); }
		if(this->m_port == GPIOE) { (RCC->AHBENR &= ~(1u << 21u)); }
		if(this->m_port == GPIOF) { (RCC->AHBENR &= ~(1u << 22u)); }
	}

}
