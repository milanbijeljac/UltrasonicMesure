#pragma once

#include "stm32f072x8.h"
#include "types.h"
namespace Driver
{
	class GPIO
	{
	public:
		enum class GpioPin : uint8_t {
		    P0  = 0,
		    P1  = 1,
		    P2  = 2,
		    P3  = 3,
		    P4  = 4,
		    P5  = 5,
		    P6  = 6,
		    P7  = 7,
		    P8  = 8,
		    P9  = 9,
		    P10 = 10,
		    P11 = 11,
		    P12 = 12,
		    P13 = 13,
		    P14 = 14,
		    P15 = 15
		};

		enum class Mode : uint8
		{
			InputMode = 0,
			OutputMode,
			AlternateFunctionMode,
			AnalogMode,
			IRQ_FallingTrigger,
			IRQ_RisingTrigger,
			IRQ_RisingFallingTrigger
		};

		enum class Speed : uint8
		{
			LowSpeed = 0,
			MediumSpeed,
			HighSpeed,
		};

		enum class PullUpDown : uint8
		{
			NoPull = 0,
			PullUp,
			PullDown,
			Reserved
		};

		enum class OutputType : uint8
		{
			PushPull = 0,
			OpenDrain
		};

		enum class AlternateFunctionality : uint8
		{
			AF0 = 0,
			AF1,
			AF2,
			AF3,
			AF4,
			AF5,
			AF6,
			AF7
		};

	public:
		GPIO(GPIO_TypeDef* port,
			 GpioPin GpioPin,
		     Mode Mode,
			 Speed Speed,
			 PullUpDown PullUpDown,
			 OutputType OutputType,
			 AlternateFunctionality AlternateFunctionality )
		: m_port(port),
		  m_GpioPin(GpioPin),
		  m_Moder(Mode),
		  m_Speed(Speed),
		  m_PullUpDown(PullUpDown),
		  m_OutputType(OutputType),
		  m_AlternateFunctionality(AlternateFunctionality)
		{
			GPIO_v_Init();
		}

		GPIO(GPIO_TypeDef* port,
					 GpioPin GpioPin,
				     Mode Mode,
					 Speed Speed,
					 PullUpDown PullUpDown,
					 OutputType OutputType )
				: m_port(port),
				  m_GpioPin(GpioPin),
				  m_Moder(Mode),
				  m_Speed(Speed),
				  m_PullUpDown(PullUpDown),
				  m_OutputType(OutputType)
				{
					GPIO_v_Init();
				}

		/** Method used to deinitialize port */
		void GPIO_v_DeInit();
		/** Method used to disable RCC for GPIOx */
		void GPIO_v_DisableClock();
		/** Method used to toggle pin */
		void GPIO_v_TogglePin(GPIO_TypeDef *port, GpioPin m_GpioPin);

		/* Prevent accidental copies that would re-init same peripheral */
		~GPIO() = default;

		GPIO(const GPIO&)            = delete;

		GPIO& operator=(const GPIO&) = delete;

		GPIO(GPIO&&)                 = delete;

		GPIO& operator=(GPIO&&)      = delete;

	private:
		void GPIO_v_Init();
		void GPIO_v_EnableClock();
		void GPIO_v_ModerConfig();
		void GPIO_v_SpeedConfig();
		void GPIO_v_PupdrConfig();
		void GPIO_v_OutputConfig();
		void GPIO_v_AlternateFunctionConfig();
		uint8 GPIO_u_PortCheck();
	private:
		GPIO_TypeDef* m_port;
		GpioPin m_GpioPin;
		Mode m_Moder;
		Speed m_Speed;
		PullUpDown m_PullUpDown;
		OutputType m_OutputType;
		AlternateFunctionality m_AlternateFunctionality;
	};

}

namespace Driver::GpioHelper
{
	/** Function used to read from pin of selected port */
	inline uint8 GPIO_u_ReadFromInputPin(GPIO_TypeDef* port, GPIO::GpioPin pin)
	{
		uint8 u_retVal = 0u;
		u_retVal = (uint8)((port->IDR >> static_cast<uint8>(pin)) & 0x00000001);
		return u_retVal;
	}

	/** Function used to read whole selected port */
	inline uint32 GPIO_u_ReadFromInput_port(GPIO_TypeDef *port)
	{
		uint32 u_retVal = 0u;
		u_retVal = (uint32) port->IDR;
		return u_retVal;
	}

	/** Function used to write to pin of selected port */
	inline void GPIO_v_WriteToOutputPin(GPIO_TypeDef *port, GPIO::GpioPin pin, FlagStatus status)
	{
		if(status == SET)
		{
			/* Write 1 to the out data register to the bit fiend corresponding to bit number */
			port->ODR |= (1 << static_cast<uint8>(pin));
		}
		else
		{
			port->ODR &= ~(1 << static_cast<uint8>(pin));
		}
	}

	/** Function used to write whole selected port */
	inline void GPIO_v_WriteToOutput_port(GPIO_TypeDef *port, uint32 u_value)
	{
		port->ODR = u_value;
	}

	/* Function used to toggle pin with ODR register */
	inline void GPIO_v_TogglePin(GPIO_TypeDef *port, GPIO::GpioPin pin)
	{
		port->ODR ^= (1 << static_cast<uint8>(pin));
	}

	/* Function used to set/reset bit with BSRR register */
	inline void GPIO_v_BitSetResetConfig(GPIO_TypeDef *port, GPIO::GpioPin pin, FlagStatus status)
	{
		if(status == SET)
		{
			port->BSRR |= 1u << static_cast<uint8>(pin);
		}
		else
		{
			port->BSRR &= ~(1u << (static_cast<uint8>(pin) + 16u));
		}
	}

	/** Function used to toggle bit with BSRR register */
	inline void GPIO_v_BitToggleBsrr(GPIO_TypeDef *port, GPIO::GpioPin pin, FlagStatus status)
	{
		if(status == SET)
		{
			port->BSRR ^= 1u << static_cast<uint8>(pin);
		}
		else
		{
			port->BSRR ^= 1u << (static_cast<uint8>(pin) + 16u);
		}
	}
}
