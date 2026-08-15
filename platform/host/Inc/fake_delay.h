#pragma once

#include "i_delay.h"

namespace platform::host
{
	/** IDelay test double: records requested delays instead of spinning. */
	class FakeDelay final : public hal::IDelay
	{
	public:
		void us(uint16 microseconds) noexcept override { m_last_us = microseconds; m_total_us += microseconds; }
		void ms(uint16 milliseconds) noexcept override { m_last_ms = milliseconds; m_total_us += static_cast<uint32>(milliseconds) * 1000u; }

		[[nodiscard]] uint16 last_us()  const noexcept { return m_last_us; }
		[[nodiscard]] uint16 last_ms()  const noexcept { return m_last_ms; }
		[[nodiscard]] uint32 total_us() const noexcept { return m_total_us; }

	private:
		uint16 m_last_us{0};
		uint16 m_last_ms{0};
		uint32 m_total_us{0};
	};
}
