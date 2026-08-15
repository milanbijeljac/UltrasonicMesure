#pragma once

#include "i_digital_output.h"

namespace platform::host
{
	/** In-memory IDigitalOutput for host unit tests. Records state + call counts. */
	class FakeDigitalOutput final : public hal::IDigitalOutput
	{
	public:
		void set()   noexcept override { m_state = true;  ++m_set_count;   }
		void clear() noexcept override { m_state = false; ++m_clear_count; }

		[[nodiscard]] bool state()       const noexcept { return m_state; }
		[[nodiscard]] unsigned set_count()   const noexcept { return m_set_count; }
		[[nodiscard]] unsigned clear_count() const noexcept { return m_clear_count; }

	private:
		bool     m_state{false};
		unsigned m_set_count{0};
		unsigned m_clear_count{0};
	};
}
