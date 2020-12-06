#pragma once

#include "log.hpp"
#include "debug.hpp"

#ifdef AGL_DEBUG
	#define AGL_CORE_ASSERT(condition, ...) \
		do { \
			if(!condition) \
			{ \
				AGL_CORE_DEBUG("Assertion triggered at:\n", AGL_CODE_POINT, "On: ", #condition, "\n", __VA_ARGS__); \
				AGL_HALT(); \
			} \
		} while(false)

	#define AGL_CORE_ASSERT(condition, ...) \
			do { \
				if(!condition) \
				{ \
					AGL_DEBUG("Assertion triggered at:\n", AGL_CODE_POINT, "On: ", #condition, "\n", __VA_ARGS__); \
					AGL_HALT(); \
				} \
			} while(false)
#endif