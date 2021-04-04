#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <mutex>
#include <sstream>
#include <vector>
#include <chrono> 
#include <ctime>

#include "debug.hpp"

namespace agl
{
	namespace system
	{
		/// <summary>
		/// A simple class to provide logging to a stream.
		/// The logging methods must be provided with a message and optionally some arguments.
		/// There are two methods to emplace the string version of an argument in the message:
		/// 1. Use indexed brackets {index}, where index is a valid index of the argument provided in variadic parameter list
		/// 2. Use unindexed brackets {}, which will emplace the next in order argument from the variadic parameter list. 
		///	If the second method is used, the argument will not be considered as an indexed argument 
		/// and thus the first argument's index will be incremented by one each unindexed brackets in the message.
		/// </summary>
		class CLogInstance
		{
			friend class CLog;

			/// <summary>
			/// Set the output 'target_' to 'target'
			/// </summary>
			/// <param name="target">The output target</param>
			CLogInstance(std::ostream &target);

			/// <summary>
			/// Copy the logger instance.
			/// </summary>
			/// <param name="other">The instance to be copied from</param>
			CLogInstance(const CLogInstance &other);

			/// <summary>
			/// Log the message.
			/// </summary>
			/// <param name="message">The format message</param>
			/// <param name="...args">Optional arguments</param>
			template <typename... Args>	void log(std::string &&message, Args&&... args);

			/// <summary>
			/// Parse the arguments and convert them to string if possible.
			/// </summary>
			/// <param name="t">The argument's tuple</param>
			/// <returns>
			/// The parsed arguments vector
			/// </returns>
			template <typename Tuple, std::size_t... Sequence> std::vector<std::string> parseArgs(Tuple &&t, std::index_sequence<Sequence...>) const;

			/// <summary>
			/// Convert the argument to a string.
			/// </summary>
			/// <param name="arg">The element to be converted</param>
			/// <returns>
			/// String version of an element
			/// </returns>
			template <typename T> std::string toString(T &&arg) const;

			/// <summary>
			/// Combine the final message and emplace the arguments in it.
			/// </summary>
			/// <param name="message">The format message</param>
			/// <param name="args">Optional arguments</param>
			/// <returns>
			/// The message
			/// </returns>
			std::string combineMessage(std::string &&message, std::vector<std::string> &&args) const;

			std::ostream &target_;
			std::mutex streamLock_;
		};

		/// <summary>
		/// A class providing different types of messages to be logged, that may have other output destinations.
		/// </summary>
		class CLog
		{
		public:
			/// <summary>
			/// Default move constructor.
			/// </summary>
			/// <param name=""></param>
			CLog(CLog&&) = default;

			/// <summary>
			/// Log trace message.
			/// </summary>
			/// <param name="message">The format message</param>
			/// <param name="...args">Optional arguments</param>
			template <typename... Args> void trace(std::string &&message, Args&&... args);

			/// <summary>
			/// Log info message.
			/// </summary>
			/// <param name="message">The format message</param>
			/// <param name="...args">Optional arguments</param>
			template <typename... Args> void info(std::string &&message, Args&&... args);

			/// <summary>
			/// Log warning message.
			/// </summary>
			/// <param name="message">The format message</param>
			/// <param name="...args">Optional arguments</param>
			template <typename... Args> void warn(std::string &&message, Args&&... args);

			/// <summary>
			/// Log error message.
			/// </summary>
			/// <param name="message">The format message</param>
			/// <param name="...args">Optional arguments</param>
			template <typename... Args> void error(std::string &&message, Args&&... args);

			/// <summary>
			/// Log critical message.
			/// </summary>
			/// <param name="message">The format message</param>
			/// <param name="...args">Optional arguments</param>
			template <typename... Args> void critical(std::string &&message, Args&&... args);

#ifdef AGL_DEBUG
			/// <summary>
			/// Log trace message.
			/// Only exists when the AGL_DEBUG macro is defined.
			/// </summary>
			/// <param name="message">The format message</param>
			/// <param name="...args">Optional arguments</param>
			template <typename... Args> void debug(std::string &&message, Args&&... args);
#endif

			/// <summary>
			/// Change the output destination of the trace logger.
			/// </summary>
			/// <param name="target">The destination</param>
			void traceTarget(std::ostream &target);

			/// <summary>
			/// Change the output destination of the info logger.
			/// </summary>
			/// <param name="target">The destination</param>
			void infoTarget(std::ostream &target);

			/// <summary>
			/// Change the output destination of the warning logger.
			/// </summary>
			/// <param name="target">The destination</param>
			void warnTarget(std::ostream &target);

			/// <summary>
			/// Change the output destination of the error logger.
			/// </summary>
			/// <param name="target">The destination</param>
			void errorTarget(std::ostream &target);

			/// <summary>
			/// Change the output destination of the critical logger.
			/// </summary>
			/// <param name="target">The destination</param>
			void criticalTarget(std::ostream &target);

			/// <summary>
			/// Get the prefix that will be added to every message.
			/// </summary>
			/// <returns>
			/// The prefix
			/// </returns>
			const std::string& getPrefix() const;

			/// <summary>
			/// Set the prefix that will be added to every message.
			/// </summary>
			/// <param name="prefix">The prefix</param>
			void setPrefix(const std::string &prefix);

			/// <summary>
			/// Set the prefixes that will be added to every message.
			/// </summary>
			/// <param name="prefix">The prefixes</param>
			void setPrefix(const std::vector<std::string> &prefix);

		private:
			friend class CLogger;

			/// <summary>
			/// A full constructor to set the output destinations for all of the loggers.
			/// </summary>
			/// <param name="t">The trace's ouput destination.</param>
			/// <param name="i">The info's ouput destination.</param>
			/// <param name="w">The warning's ouput destination.</param>
			/// <param name="e">The error's ouput destination.</param>
			/// <param name="c">The critical error's ouput destination.</param>
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
		};

		/// <summary>
		/// A class providing the core and client loggers.
		/// </summary>
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
	}
}
	/*
	* TRACE - function enter / end
	* INFO - print info
	* WARN - issue that may cause trouble
	* ERROR - recoverable error
	* CRITICAL - unrecoverable error
	*/

#define AGL_CORE_LOG_TRACE(message, ...)	::agl::system::CLogger::getCoreLogger().trace(AGL_CODE_POINT + message, __VA_ARGS__)
#define AGL_CORE_LOG_INFO(message, ...)		::agl::system::CLogger::getCoreLogger().info(message, __VA_ARGS__)
#define AGL_CORE_LOG_WARNING(message, ...)	::agl::system::CLogger::getCoreLogger().warn(message, __VA_ARGS__)
#define AGL_CORE_LOG_ERROR(message, ...)	::agl::system::CLogger::getCoreLogger().error(message, __VA_ARGS__)
#define AGL_CORE_LOG_CRITICAL(message, ...)	::agl::system::CLogger::getCoreLogger().critical(message, __VA_ARGS__)

#define AGL_LOG_TRACE(message, ...)		::agl::system::CLogger::getClientLogger().trace(AGL_CODE_POINT + message, __VA_ARGS__)
#define AGL_LOG_INFO(message, ...)		::agl::system::CLogger::getClientLogger().info(message, __VA_ARGS__)
#define AGL_LOG_WARNING(message, ...)	::agl::system::CLogger::getClientLogger().warn(message, __VA_ARGS__)
#define AGL_LOG_ERROR(message, ...)		::agl::system::CLogger::getClientLogger().error(message, __VA_ARGS__)
#define AGL_LOG_CRITICAL(message, ...)  ::agl::system::CLogger::getClientLogger().critical(message, __VA_ARGS__)

#ifdef AGL_DEBUG
	#define AGL_CORE_LOG_DEBUG(message, ...) ::agl::system::CLogger::getCoreLogger().debug(message, __VA_ARGS__)
	#define AGL_LOG_DEBUG(message, ...)		 ::agl::system::CLogger::getClientLogger().debug(message, __VA_ARGS__)
#else 
	#define AGL_CORE_LOG_DEBUG(...)
	#define AGL_LOG_DEBUG(...)		
#endif
