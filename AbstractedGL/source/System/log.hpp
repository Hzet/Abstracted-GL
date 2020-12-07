#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include "debug.hpp"

namespace agl
{
	class CLogInstance
	{
		friend class CLog;

		CLogInstance(std::ostream &target);
		CLogInstance(const CLogInstance &other);

		template <typename... Args>	void log(Args&&... msgs);

		std::ostream &target_;
		std::mutex streamLock_;
	};

	class CLog
	{
	public:
		CLog(CLog&&) = default;

		template <typename... Args> void trace(Args&&... msgs);
		template <typename... Args> void info(Args&&... msgs);
		template <typename... Args> void warn(Args&&... msgs);
		template <typename... Args> void error(Args&&... msgs);
		template <typename... Args> void critical(Args&&... msgs);
	
		void traceTarget(std::ostream &target);
		void infoTarget(std::ostream &target);
		void warnTarget(std::ostream &target);
		void errorTarget(std::ostream &target);
		void criticalTarget(std::ostream &target);

#ifdef AGL_DEBUG
		template <typename... Args> void debug(Args&&... msgs);
#endif

		const std::string& getPrefix() const;
		void setPrefix(const std::string &prefix);
		void setPrefix(const std::vector<std::string> &prefix);

		const std::string& getSuffix() const;
		void setSuffix(const std::string &suffix);
		void setSuffix(const std::vector<std::string> &suffix);

	private:
		friend class CLogger;	
		
		CLog(std::ostream &t, std::ostream &i, std::ostream &w, std::ostream &e, std::ostream &c);

		std::unique_ptr<CLogInstance> traceLog_;
		std::unique_ptr<CLogInstance> infoLog_;
		std::unique_ptr<CLogInstance> warnLog_;
		std::unique_ptr<CLogInstance> errorLog_;
		std::unique_ptr<CLogInstance> criticalLog_;

#ifdef AGL_DEBUG
		std::unique_ptr<CLogInstance> debugLog_;
#endif

		std::string prefix_;
		std::string suffix_;
	};

	class CLogger
	{
	public:
		static CLog& getCoreLogger();
		static CLog& getClientLogger();

	private:
		static std::unique_ptr<CLog> CoreLog_;
		static std::unique_ptr<CLog> ClientLog_;
	};
#include "log.inl"

	/*
	* TRACE - function enter / end
	* INFO - print info
	* WARN - issue that may cause trouble
	* ERROR - recoverable error
	* CRITICAL - unrecoverable error
	*/

#define AGL_CORE_LOG_TRACE(message, ...)	agl::CLogger::getCoreLogger().trace(AGL_CODE_POINT, message, __VA_ARGS__)
#define AGL_CORE_LOG_INFO(message, ...)		agl::CLogger::getCoreLogger().info(message, __VA_ARGS__)
#define AGL_CORE_LOG_WARNING(message, ...)	agl::CLogger::getCoreLogger().warn(message, __VA_ARGS__)
#define AGL_CORE_LOG_ERROR(message, ...)	agl::CLogger::getCoreLogger().error(message, __VA_ARGS__)
#define AGL_CORE_LOG_CRITICAL(message, ...)	agl::CLogger::getCoreLogger().critical(message, __VA_ARGS__)

#define AGL_LOG_TRACE(message, ...)		agl::CLogger::getClientLogger().trace(AGL_CODE_POINT, message, __VA_ARGS__)
#define AGL_LOG_INFO(message, ...)		agl::CLogger::getClientLogger().info(message, __VA_ARGS__)
#define AGL_LOG_WARNING(message, ...)	agl::CLogger::getClientLogger().warn(message, __VA_ARGS__)
#define AGL_LOG_ERROR(message, ...)		agl::CLogger::getClientLogger().error(message, __VA_ARGS__)
#define AGL_LOG_CRITICAL(message, ...)  agl::CLogger::getClientLogger().critical(message, __VA_ARGS__)

#ifdef AGL_DEBUG
	#define AGL_CORE_DEBUG(message, ...) agl::CLogger::getCoreLogger().debug(message, __VA_ARGS__)
	#define AGL_DEBUG(message, ...)		 agl::CLogger::getClientLogger().debug(message, __VA_ARGS__)
#else 
	#define AGL_CORE_DEBUG(...)
	#define AGL_DEBUG(...)		
#endif
}