#pragma once
#include "log.hpp"
#include "debug.hpp"

#ifdef AGL_DEBUG
	#define AGL_ASSERTION_LOG_MARK_COMA(assertionName) "\n--------------------------------------", assertionName, "--------------------------------------\n"

	#define AGL_CORE_ASSERT(condition, ...) AGL_ASSERT_IMPL(condition, "CORE BEGIN", "CORE END", __VA_ARGS__)

	#define AGL_ASSERT(condition, ...) AGL_ASSERT_IMPL(condition, "ASSERT BEGIN", "ASSERT END", __VA_ARGS__)

	#define AGL_ASSERT_IMPL(condition, assertionStart, assertionEnd, ...) \
		do \
		{ \
			if(!condition) { \
				AGL_DEBUG_LOG_IMPL(AGL_ASSERTION_LOG_MARK_COMA(assertionStart), AGL_CODE_NAME_COMA, "- Asertion failed! -\nOn: ", #condition, "\nMessage: ", __VA_ARGS__, AGL_ASSERTION_LOG_MARK_COMA(assertionEnd)); \
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