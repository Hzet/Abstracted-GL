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

#define AGL_LOG(message, ...) agl::CLog::SendMessage(x, __VA_ARGS__)

#define AGL_ERROR_LOG(message, ...) \
	do { \
		std::ofstream file("error-dump.log", std::ios::out | std::ios::app); \
		agl::CLog::SendOneMessage(file, message, __VA_ARGS__); \
	} while(false) \

#ifdef AGL_DEBUG
	#define AGL_DEBUG_LOG_IMPL(...) \
		do { \
			std::ofstream file("debug.log", std::ios::out | std::ios::app); \
			agl::CLog::SendOneMessage(file, __VA_ARGS__); \
		} while(false) \

	#define AGL_DEBUG_LOG(message, ...) \
		do { \
			AGL_DEBUG_LOG_IMPL(AGL_CODE_NAME_COMA, message, __VA_ARGS__); \
		} while(false) \

#endif