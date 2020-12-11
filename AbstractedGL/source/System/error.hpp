#pragma once 

#include "log.hpp"
#include "assert.hpp"
#include "exception.hpp"
#include "error.hpp"

#ifdef AGL_DEBUG
	#define AGL_CORE_CRITICAL(message, code, ...) \
		{ \
			AGL_CORE_ASSERT(false, std::string("AGL error: [{}]\n") + message, code, __VA_ARGS__); \
		}

	#define AGL_CORE_ERROR(message, code, ...) \
		{ \
			AGL_CORE_ASSERT(false, std::string("AGL error: [{}]\n") + message, code, __VA_ARGS__); \
		}

	#define AGL_CRITICAL(message, code, ...) \
		{ \
			AGL_ASSERT(false, std::string("AGL error: [{}]\n") + message, code, __VA_ARGS__); \
		}

	#define AGL_ERRORL(message, code, ...) \
		{ \
			AGL_ASSERT(false, std::string("AGL error: [{}]\n") + message, code, __VA_ARGS__); \
		}
#else

	#define AGL_CORE_CRITICAL(message, code, ...) \
		{ \
			AGL_CORE_LOG_CRITICAL(std::string("AGL error: [{}]\n") + message, code, __VA_ARGS__); \
			throw ::agl::system::CException("AbstractedGL core encountered a critical error!", code); \
		}

	#define AGL_CORE_ERROR(message, code, ...) \
		{ \
			AGL_CORE_LOG_ERROR(std::string("AGL error: [{}]\n") + message, code, __VA_ARGS__); \
		}

	#define AGL_CRITICAL(message, code, ...) \
		{ \
			AGL_LOG_CRITICAL(false, std::string("AGL error: [{}]\n") + message, code, __VA_ARGS__); \
			throw ::agl::system::CException("Critical error occured!", code); \
		}

	#define AGL_ERROR(message, code, ...) \
		{ \
			AGL_LOG_ERROR(std::string("AGL error: [{}]\n") + message, code, __VA_ARGS__); \
		}
#endif