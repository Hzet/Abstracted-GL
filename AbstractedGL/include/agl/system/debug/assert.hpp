#pragma once

#include "core/misc/log.hpp"

#ifdef AGL_DEBUG
	#define AGL_CORE_ASSERT(condition, message, ...) \
		do { \
			if(!(condition)) \
			{ \
				AGL_CORE_LOG_TRACE(std::string("\nAssertion failed on: {}\n") + message, #condition, __VA_ARGS__); \
				AGL_HALT(); \
			} \
		} while(false)

	#define AGL_ASSERT(condition, message, ...) \
		do { \
			if(!(condition)) \
			{ \
				AGL_LOG_TRACE(std::string("\nAssertion failed on: {}\n") + message, #condition, __VA_ARGS__); \
				AGL_HALT(); \
			} \
		} while(false)
#else
	#define AGL_CORE_ASSERT(condition, message, ...) \
		do { \
			(void)sizeof(condition); \
		} while(false)

	#define AGL_ASSERT(condition, message, ...) \
		do { \
			(void)sizeof(condition); \
		} while(false)
#endif