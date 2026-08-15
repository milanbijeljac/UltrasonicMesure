#pragma once

#include "sensor_base.h"
#include "types.h"
#include "i_capture_timer.h"
#include "i_delay.h"
#include "i_digital_output.h"

namespace Sensor
{
	class HCSR04 : public SensorBase
	{
	public:

		enum class Unit : uint8_t
		{
			centimeters = 0,
			inches
		};

		HCSR04(const std::string_view& name,
			   hal::IDigitalOutput& trig,
			   hal::ICaptureTimer& echo,
			   hal::IDelay& delay) : SensorBase(name), m_trig(trig), m_echo(echo), m_delay(delay)
		{

		}

		[[nodiscard]] float measure(Unit unit);

		~HCSR04() = default;

		[[nodiscard]] static float to_distance(uint32 us, Unit unit);

	private:
        hal::IDigitalOutput& m_trig;
        hal::ICaptureTimer&  m_echo;
        hal::IDelay&         m_delay;
	};
}
