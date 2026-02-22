#pragma once

#include "../../sensor_base.h"
#include "types.h"

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

		HCSR04(const std::string_view& name) : SensorBase(name)
		{

		}

		float HCSR04_f_CalculateDistance(uint32 capture, HCSR04::Unit unit);
		~HCSR04() = default;

	private:

	};
}
