#include "event-static-queue.hpp"
#include "assert.hpp"

namespace agl
{
	namespace system
	{
		CEventQueue::CEventQueue()
			: first_(0u),
			count_(0u)
		{
		}

		const std::size_t CEventQueue::count() const
		{
			return count_;
		}

		const agl::SEvent& CEventQueue::pop() const
		{
			AGL_CORE_ASSERT(count_ != 0, "Cannot pop from an empty queue");

			const std::size_t prevFirst = first_;

			first_ = (first_ + 1u) % QueueCount;
			count_--;

			return queue_[prevFirst];
		}

		void CEventQueue::push(const SEvent &event)
		{
			queue_[getLast()] = event;
			count_++;

			if (count_ == QueueOverload)
			{
				count_ = QueueCount;
				first_ = (first_ + 1u) % QueueCount;
			}
		}

		inline const std::size_t CEventQueue::getFirst() const
		{
			return first_;
		}

		const std::size_t CEventQueue::getLast() const
		{
			return (first_ + count_) % QueueCount;
		}
	}
}
