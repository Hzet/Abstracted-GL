#pragma once

#include "log.hpp"

#ifdef AGL_DEBUG
	#define AGL_CORE_ASSERT(condition, message, ...) \
		do { \
			if(!(condition)) \
			{ \
				AGL_CORE_LOG_DEBUG("Assertion failed!\nAssertion triggered at:\n{}\nOn: {}\n" + std::string(message), AGL_CODE_POINT, #condition, __VA_ARGS__); \
				AGL_HALT(); \
			} \
		} while(false)

	#define AGL_ASSERT(condition, message, ...) \
		do { \
			if(!(condition)) \
			{ \
				AGL_LOG_DEBUG("Assertion failed!\nAssertion triggered at: {}\nOn: {}\n" + std::string(message), AGL_CODE_POINT, #condition, __VA_ARGS__); \
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