#pragma once

#include <string>

namespace Sensor
{
	class SensorBase
	{
	public:

		SensorBase(const std::string_view& name) : m_name(name)
		{

		}

		std::string_view getName() const noexcept { return m_name; };

	private:
		const std::string_view m_name;

	};
}
