#include "utility/threads/mutex.hpp"

namespace agl
{
	void CMutex::lock()
	{
		peersCount_++;
		mutex_.lock();
	}

	void CMutex::unlock()
	{
		peersCount_--;
		mutex_.unlock();
	}

	bool CMutex::try_lock()
	{
		if (!mutex_.tryLock())
			return false;

		peersCount_++;
		return true;
	}

	std::uint64_t agl::CMutex::getPeersCount() const
	{

	}
}

