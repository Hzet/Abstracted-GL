#pragma once
#include "utility/threads/mutex.hpp"

namespace agl
{
	template <typename T>
	class TLockBase
	{
	public:
		ILock(CMutex &mutex);
		virtual ~ILock();

	private:
		CMutex &mutex_;
	};

	enum ELockType
	{
		GUARD,
		SCOPE,
		UNIQUE,
		INVALID
	};

	template <ELockType = INVALID>
	class TLock
	{
	};

	template <>
	class TLock<GUARD>
		:
	{
	public:

	private:
	};
}

