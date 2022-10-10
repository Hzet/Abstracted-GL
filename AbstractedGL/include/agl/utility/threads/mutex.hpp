#pragma once
#include <mutex>

namespace agl
{
	class CMutex
	{
	public:
		void lock();
		bool try_lock();
		void unlock();
		std::uint64_t getPeersCount() const;

	private:
		template <typename T> friend class TLockBase;

		std::mutex mutex_;
		std::uint64_t peersCount_;
	};
}