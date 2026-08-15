#pragma once

#include <string_view>

namespace Sensor
{
	class SensorBase
	{
	public:

		SensorBase(const std::string_view& name) : m_name(name)
		{

		}

		[[nodiscard]] std::string_view get_name() const noexcept { return m_name; };

	protected:
		/* Protected + non-virtual: derived classes can destroy the base
		 * subobject, but a SensorBase* cannot be deleted (which would be UB
		 * with a non-virtual base destructor). No vtable cost. */
		~SensorBase() = default;

	private:
		const std::string_view m_name;

	};
}
