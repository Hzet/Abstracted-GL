#pragma once

#include <cstdint>
#include "event.hpp"

namespace agl
{
	namespace system
	{
		/// <summary>
		/// A queue that has a static buffer of 'QueueCount' for storing pending events.
		/// </summary>
		class CEventQueue
		{
		public:
			constexpr static std::uint32_t QueueCount = 512u;
			constexpr static std::uint32_t QueueOverload = QueueCount + 1u;

			/// <summary>
			/// Set the 'first_' and 'count_' to zero.
			/// </summary>
			CEventQueue();

			/// <summary>
			/// Get the count of pending events.
			/// </summary>
			std::uint32_t count() const; // number of events pending to be processed

			/// <summary>
			/// Get the last occurred event and remove it from the pending event list.
			/// </summary>
			/// <returns>
			/// The element
			/// </returns>
			const SEvent& pop() const;

			/// <summary>
			/// Push a new element at the end of the queue.
			/// </summary>
			/// <param name="event">The event</param>
			void push(const SEvent &event);

		private:
			inline const std::uint32_t getFirst() const;
			inline const std::uint32_t getLast() const;

			SEvent queue_[QueueCount];

			mutable std::uint32_t first_;
			mutable std::uint32_t count_;
		};
	}
}