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

#define AGL_BEGIN_TAG(tag) "\n---------------------------------", tag, " BEGIN", "---------------------------------\n"
#define AGL_END_TAG(tag) "\n---------------------------------", tag, " END", "---------------------------------\n"

#define AGL_LOG(message, ...) agl::CLog::SendMessage(x, __VA_ARGS__)

#define AGL_LOG_TAGGED(tag, message, ...) agl::CLog::SendMessage(AGL_BEGIN_TAG(tag), message, __VA_ARGS__, AGL_END_TAG(tag))

#define AGL_LOG_FILE(filename, message, ...) \
	{ \
		std::ofstream file(filename, std::ios::out | std::ios::app); \
		agl::CLog::SendOneMessage(file, message, __VA_ARGS__); \
		file.close(); \
	} \

#define AGL_LOG_FILE_TAGGED(filename, tag, message, ...) AGL_LOG_FILE(filename, AGL_BEGIN_TAG(tag), message, __VA_ARGS__, AGL_END_TAG(tag));

#define AGL_LOG_STREAM(stream, message, ...) agl::CLog::SendOneMessage(stream, message, __VA_ARGS__)

#define AGL_LOG_STREAM_TAGGED(stream, tag, message, ...)  agl::CLog::SendOneMessage(stream, AGL_BEGIN_TAG(tag), message, __VA_ARGS__, AGL_END_TAG(tag))

#define AGL_ERROR_LOG(message, ...) AGL_LOG_FILE_TAGGED("error-dump.log", AGL_CODE_NAME_COMA, message, __VA_ARGS__)

#define AGL_ERROR_LOG_STREAM(stream, message, ...) AGL_LOG_STREAM(stream, AGL_CODE_NAME_COMA, message, __VA_ARGS__)

#ifdef AGL_DEBUG
#define AGL_DEBUG_LOG(message, ...) AGL_LOG_FILE_TAGGED("debug-dump.log", AGL_CODE_NAME_COMA, message, __VA_ARGS__)

#endif