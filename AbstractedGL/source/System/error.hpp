#pragma once 

#include "log.hpp"
#include "assert.hpp"
#include "exception.hpp"

#ifdef AGL_DEBUG
	#define AGL_CORE_CRITICAL(message, ...) \
		{ \
			AGL_CORE_ASSERT(false, message, __VA_ARGS__); \
		}

	#define AGL_CORE_ERROR(message, ...) \
		{ \
			AGL_CORE_ASSERT(false, message, __VA_ARGS__); \
		}

	#define AGL_CRITICAL(message, ...) \
		{ \
			AGL_ASSERT(false, message, __VA_ARGS__); \
		}

	#define AGL_ERRORL(message, ...) \
		{ \
			AGL_ASSERT(false, message, __VA_ARGS__); \
		}
#else

	#define AGL_CORE_CRITICAL(message, ...) \
		{ \
			AGL_CORE_LOG_CRITICAL(message, __VA_ARGS__); \
			throw ::agl::exception::CException("AbstractedGL core encountered a critical error!"); \
		}

	#define AGL_CORE_ERROR(message, ...) \
		{ \
			AGL_CORE_LOG_ERROR(message, __VA_ARGS__); \
		}

	#define AGL_CRITICAL(message, ...) \
		{ \
			AGL_LOG_CRITICAL(false, message, __VA_ARGS__); \
			throw ::agl::exception::CException("Critical error occured!"); \
		}

	#define AGL_ERROR(message, ...) \
		{ \
			AGL_LOG_ERROR(message, __VA_ARGS__); \
		}
#endif