#include "HCSR04.h"

namespace Sensor
{
	float HCSR04::to_distance(uint32 us, HCSR04::Unit unit)
	{
		if(unit == HCSR04::Unit::centimeters)
		{
			return (float)us / 58.0f;
		}
		else
		{
			return (float)us / 148.0f;
		}
	}

	float HCSR04::measure(HCSR04::Unit unit)
	{
		m_echo.start();
		m_trig.set();
		m_delay.us(10);
		m_trig.clear();

		m_delay.ms(60);
		return to_distance(m_echo.last_pulse_width_us(), unit);
	}
}
