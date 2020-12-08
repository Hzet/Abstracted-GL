#pragma once

#include <cstddef>
#include "event.hpp"

namespace agl
{
	class CEventQueue
	{
	public:
		CEventQueue();

		constexpr static std::size_t QueueCount = 512u;
		constexpr static std::size_t QueueOverload = QueueCount + 1u;

		const std::size_t count() const; // number of events pending to be processed
		
		const SEvent& pop() const;
		void push(const SEvent &event);

	private:
		inline const std::size_t getFirst() const;
		inline const std::size_t getLast() const;

		SEvent queue_[QueueCount];

		mutable std::size_t first_;
		mutable std::size_t count_;
	};
}