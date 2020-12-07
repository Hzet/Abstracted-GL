#pragma once 

#include "log.hpp"
#include "assert.hpp"
#include "exception.hpp"

#ifdef AGL_DEBUG
	#define AGL_CORE_CRITICAL(call, comparison, expected, message, ...) \
		{ \
			auto result = call; \
			AGL_CORE_ASSERT(result comparison call, "Unrecoverable error has occured!\nExpected: [", result, " ", #comparison, " ", expected,  "]\nResult: [", result, "]\nDescription: ", message, __VA_ARGS__); \
		}

	#define AGL_CRITICAL(call, comparison, expected, message, ...) \
		{ \
			auto result = call; \
			AGL_ASSERT(result comparison call, "Unrecoverable error has occured!\nExpected: [", result, " ", #comparison, " ", expected,  "]\nResult: [", result, "]\nDescription: ", message, __VA_ARGS__); \
		}
#else
	#define AGL_CORE_CRITICAL(call, comparison, expected, message, ...) \
		{ \
			auto result = call; \
			if(!(result comparison expected)) \
			{ \
				AGL_CORE_LOG_CRITICAL("Call to: ", #call, " has failed!\nExpected: [", expected, "]\nResult: [", result, "]\nDescription: ", message, __VA_ARGS__); \
				throw agl::exception::CException("Unrecoverable error has occured!"); \
			} \
		}

	#define AGL_CRITICAL(call, comparison, exprected, message, ...) \
		{ \
			auto result = call; \			
			if(!(result comparison expected)) \
			{ \
				AGL_LOG_CRITICAL("Call to: ", #call, " has failed!\nExpected: [", expected, "]\nResult: [", result, "]\nDescription: ", message, __VA_ARGS__); \
				throw agl::exception::CException("Unrecoverable error has occured!"); \
			} \
		}
#endif