#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
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

#define AGL_CORE_TRACE(message, ...)		  agl::CLogger::getCoreLogger().trace(message, __VA_ARGS__)
#define AGL_CORE_INFO(message, ...)			  agl::CLogger::getCoreLogger().info(message, __VA_ARGS__)
#define AGL_CORE_WARNING(message, ...)		  agl::CLogger::getCoreLogger().warn(message, __VA_ARGS__)
#define AGL_CORE_ERROR(message, ...)		  agl::CLogger::getCoreLogger().error(message, __VA_ARGS__)
#define AGL_CORE_CRITICAL_ERROR(message, ...) agl::CLogger::getCoreLogger().critical(message, __VA_ARGS__)

#define AGL_TRACE(message, ...)			 agl::CLogger::getClientLogger().trace(message, __VA_ARGS__)
#define AGL_INFO(message, ...)			 agl::CLogger::getClientLogger().info(message, __VA_ARGS__)
#define AGL_WARNING(message, ...)		 agl::CLogger::getClientLogger().warn(message, __VA_ARGS__)
#define AGL_ERROR(message, ...)			 agl::CLogger::getClientLogger().error(message, __VA_ARGS__)
#define AGL_CRITICAL_ERROR(message, ...) agl::CLogger::getClientLogger().critical(message, __VA_ARGS__)

#ifdef AGL_DEBUG

	#define AGL_CODE_POINT "\nFilename: ", AGL_LINE, "\nFunction: ", AGL_FUNC_NAME, "\nLine: ", AGL_LINE, "\n"

	#define AGL_CORE_DEBUG(message, ...) agl::CLogger::getCoreLogger().debug(message, __VA_ARGS__)
	#define AGL_DEBUG(message, ...)		 agl::CLogger::getClientLogger().debug(message, __VA_ARGS__)
#endif
}