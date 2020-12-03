#pragma once

#include <cstddef>
#include "event.hpp"

namespace agl
{
	class CEventQueue
	{
	public:
		constexpr static std::size_t QueueCount = 512u;
		constexpr static std::size_t QueueOverload = QueueCount + 1u;

		const std::size_t pending() const; // number of events pending to be processed
		
		const SEvent& popFront() const;
		void pushBack(const SEvent &event);

	private:
		inline const std::size_t getFirst() const;
		inline const std::size_t getLast() const;

		SEvent queue_[QueueCount];

		mutable std::size_t first_ = 0u;
		mutable std::size_t count_ = 0u;
	};
}