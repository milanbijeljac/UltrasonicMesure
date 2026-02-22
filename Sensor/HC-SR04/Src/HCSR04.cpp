#include "../Inc/HCSR04.h"

namespace Sensor
{
	float HCSR04::HCSR04_f_CalculateDistance(uint32 capture, HCSR04::Unit unit)
	{
		if(unit == HCSR04::Unit::centimeters)
		{
			return (float)capture / 58.0f;
		}
		else
		{
			return (float)capture / 148.0f;
		}
	}
}
