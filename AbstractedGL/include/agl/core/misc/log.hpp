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

#include "system/debug/debug.hpp"

namespace agl
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
	class log_instance
	{
	public:
		/// <summary>
		/// Produce the final output string based on the 'message' and its 'arguments'.
		/// </summary>
		/// <param name="message">The format message</param>
		/// <param name="...args">Optional arguments</param>
		/// <returns>The message</returns>
		template <typename... Args> static std::string get_message(std::string &&message, Args&&... args);

	private:
		friend class log;

		/// <summary>
		/// Parse the arguments and convert them to string if possible.
		/// </summary>
		/// <param name="t">The argument's tuple</param>
		/// <returns>
		/// The parsed arguments vector
		/// </returns>
		template <typename Tuple, std::size_t... Sequence> static std::vector<std::string> parse_args(Tuple &&t, std::index_sequence<Sequence...>);

		/// <summary>
		/// Convert the argument to a string.
		/// </summary>
		/// <param name="arg">The element to be converted</param>
		/// <returns>
		/// String version of an element
		/// </returns>
		template <typename T> static std::string to_string(T &&arg);

		/// <summary>
		/// Combine the final message and emplace the arguments in it.
		/// </summary>
		/// <param name="message">The format message</param>
		/// <param name="args">Optional arguments</param>
		/// <returns>
		/// The message
		/// </returns>
		static std::string combine_message(std::string &&message, std::vector<std::string> &&args);


		/// <summary>
		/// Set the output 'm_target' to 'target'
		/// </summary>
		/// <param name="target">The output target</param>
		log_instance(std::ostream &target);

		/// <summary>
		/// Copy the logger instance.
		/// </summary>
		/// <param name="other">The instance to be copied from</param>
		log_instance(const log_instance &other);

		/// <summary>
		/// Log the message.
		/// </summary>
		/// <param name="message">The format message</param>
		/// <param name="...args">Optional arguments</param>
		template <typename... Args>	void log(std::string &&message, Args&&... args);

		std::ostream &m_target;
		std::mutex m_stream_lock;
	};

	/// <summary>
	/// A class providing different types of messages to be logged, that may have other output destinations.
	/// </summary>
	class log
	{
	public:
		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		log(log&&) = default;

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
		/// Log trace message.
		/// </summary>
		/// <param name="message">The format message</param>
		/// <param name="...args">Optional arguments</param>
		template <typename... Args> void debug(std::string &&message, Args&&... args);

		/// <summary>
		/// Change the output destination of the trace logger.
		/// </summary>
		/// <param name="target">The destination</param>
		void set_trace_target(std::ostream &target);

		/// <summary>
		/// Change the output destination of the info logger.
		/// </summary>
		/// <param name="target">The destination</param>
		void set_info_target(std::ostream &target);

		/// <summary>
		/// Change the output destination of the warning logger.
		/// </summary>
		/// <param name="target">The destination</param>
		void set_warn_target(std::ostream &target);

		/// <summary>
		/// Change the output destination of the error logger.
		/// </summary>
		/// <param name="target">The destination</param>
		void set_error_target(std::ostream &target);

		/// <summary>
		/// Get the prefix that will be added to every message.
		/// </summary>
		/// <returns>
		/// The prefix
		/// </returns>
		const std::string& get_prefix() const;

		/// <summary>
		/// Set the prefix that will be added to every message.
		/// </summary>
		/// <param name="prefix">The prefix</param>
		void set_prefix(const std::string &prefix);

		/// <summary>
		/// Set the prefixes that will be added to every message.
		/// </summary>
		/// <param name="prefix">The prefixes</param>
		void set_prefix(const std::vector<std::string> &prefix);

	private:
		friend class logger;

		/// <summary>
		/// A full constructor to set the output destinations for all of the loggers.
		/// </summary>
		/// <param name="t">The trace's ouput destination.</param>
		/// <param name="i">The info's ouput destination.</param>
		/// <param name="w">The warning's ouput destination.</param>
		/// <param name="e">The error's ouput destination.</param>
		/// <param name="c">The critical error's ouput destination.</param>
		log(std::ostream &t, std::ostream &i, std::ostream &w, std::ostream &e, std::ostream &d);

		std::unique_ptr<log_instance> m_trace_log;
		std::unique_ptr<log_instance> m_info_log;
		std::unique_ptr<log_instance> m_warn_log;
		std::unique_ptr<log_instance> m_error_log;
		std::unique_ptr<log_instance> m_debug_log;

		std::string m_prefix;
	};

	/// <summary>
	/// A class providing the core and client loggers.
	/// </summary>
	class logger
	{
	public:
		static log& get_core_logger();
		static log& get_client_logger();

	private:
		static std::unique_ptr<log> m_core_log;
		static std::unique_ptr<log> m_client_log;
	};

#include "core/misc/log.inl"
}
	/*
	* TRACE - function enter / end
	* INFO - print info
	* WARN - issue that may cause trouble
	* ERROR - recoverable error
	* DEBUG - debugging informations
	*/

#define AGL_CORE_LOG_TRACE(message, ...)	::agl::logger::get_core_logger().trace(AGL_CODE_POINT + message, __VA_ARGS__)
#define AGL_CORE_LOG_INFO(message, ...)		::agl::logger::get_core_logger().info(message, __VA_ARGS__)
#define AGL_CORE_LOG_WARNING(message, ...)	::agl::logger::get_core_logger().warn(message, __VA_ARGS__)
#define AGL_CORE_LOG_ERROR(message, ...)	::agl::logger::get_core_logger().error(message, __VA_ARGS__)
#define AGL_CORE_LOG_DEBUG(message, ...) ::agl::logger::get_core_logger().debug(message, __VA_ARGS__)

#define AGL_LOG_TRACE(message, ...)		::agl::logger::get_client_logger().trace(AGL_CODE_POINT + message, __VA_ARGS__)
#define AGL_LOG_INFO(message, ...)		::agl::logger::get_client_logger().info(message, __VA_ARGS__)
#define AGL_LOG_WARNING(message, ...)	::agl::logger::get_client_logger().warn(message, __VA_ARGS__)
#define AGL_LOG_ERROR(message, ...)		::agl::logger::get_client_logger().error(message, __VA_ARGS__)
#define AGL_LOG_DEBUG(message, ...)		 ::agl::logger::get_client_logger().debug(message, __VA_ARGS__)
