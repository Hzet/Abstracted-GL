#pragma once
#include "log.hpp"
#include "debug.hpp"

#ifdef AGL_DEBUG
	#define AGL_CORE_ASSERT(condition, ...) AGL_ASSERT_IMPL(condition, "CORE ASSERT", __VA_ARGS__ )

	#define AGL_ASSERT(condition, ...) AGL_ASSERT_IMPL(condition, "ASSERT", __VA_ARGS__)

	#define AGL_ASSERT_IMPL(condition, tag, message, ...) \
		do \
		{ \
			if(!condition) { \
				AGL_DEBUG_LOG_TAGGED("debug-dump.log", tag, message, __VA_ARGS__); \
				AGL_HALT(); \
			} \
		} while(0) \

#else
	#define AGL_ASSERT_IMPL(...) \
		do \
		{ \
			(void)sizeof(condition); \
		} while(0) \

#endif 