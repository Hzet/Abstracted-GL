#pragma once

#include "event.hpp"

namespace agl
{
	class CEventQueue
	{
		constexpr static std::uint16_t QueueCount = 512u;
		constexpr static std::uint16_t QueueOverload = QueueCount + 1u;

		std::uint16_t pending() const; // number of events pending to be processed
		
		const SEvent& popFront() const;
		void pushBack(const SEvent &event);

	private:
		std::uint16_t current_;
		std::uint16_t occupied_;
		SEvent queue_[QueueCount];
	};
}