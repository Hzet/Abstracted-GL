#pragma once
#include "log.hpp"
#include "debug.hpp"

#ifdef AGL_DEBUG
	#define AGL_ASSERT(condition, ...) \
		do \
		{ \
			if(!condition) { \
				AGL_DEBUG_LOG("- assertion failed! -\nOn: ", #condition, "\nMessage: ", __VA_ARGS__, "\n--------------------------------NEXT--------------------------------"); \
				AGL_HALT(); \
			} \
		} while(0) \

#else
	#define AGL_ASSERT(condition) \
		do \
		{ \
			(void)sizeof(condition); \
		} while(0) \

#endif 