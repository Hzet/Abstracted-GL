#pragma once
#include <iostream>
#include <fstream>
#include <string>

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
		template <typename... Args> static void SendOneMessage(std::ostream &target, Args&&... msgs);

	private:
		static std::unique_ptr<CLogInstance> Instance_;
	};

#include "log.inl"
}

#define AGL_LOG(x, ...) agl::CLog::SendMessage(x, __VA_ARGS__)

#define AGL_ERROR_LOG(x, ...) \
	do  \
	{ \
		std::ofstream file("error-dump.log", std::ios::out | std::ios::app); \
		agl::CLog::SendOneMessage(file, x, __VA_ARGS__); \
	} \
	while(0) \

#ifdef AGL_DEBUG
	#define AGL_DEBUG_LOG(x, ...) \
		do { \
			std::ofstream file("debug.log", std::ios::out | std::ios::app); \
			agl::CLog::SendOneMessage(file, AGL_CODE_NAME_COMA, x, __VA_ARGS__); \
		} while(0) \

#endif