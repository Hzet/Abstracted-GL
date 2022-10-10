#include "utility/threads/lock.hpp"

namespace agl
{
	ILock::ILock(CMutex &mutex)
		: mutex_(mutex)
	{
		mutex_.lock();
	}

	ILock::~ILock()
	{
		mutex_.unlock();
	}
}