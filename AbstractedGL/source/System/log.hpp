#pragma once
#include <iostream>
#include <string>

#define AGL_LOG(x,...) CLog::SendMessage(x,...)

namespace agl
{
	class CLogInstance
	{
		friend class CLog;

		CLogInstance(std::ostream &target);
		CLogInstance(const CLogInstance &other);

		template <typename... Args>	void log(Args&&... msgs);

		std::ostream &target_;
	};

	class CLog
	{
	public:
		static void MessageTarget(std::ostream &target);
		template <typename... Args>	static void SendMessage(Args&&... msgs);

	private:
		static std::unique_ptr<CLogInstance> Instance_;
	};

#include "log.inl"
}