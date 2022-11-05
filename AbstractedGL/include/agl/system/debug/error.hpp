#pragma once 
#include "agl/system/debug/assert.hpp"
#include "agl/system/debug/exceptions.hpp"
#include "agl/core/misc/log.hpp"

#ifdef AGL_DEBUG
	#define AGL_CORE_EXCEPTION(exception, message, ...) \
		{ \
			AGL_CORE_ASSERT(false, "AGL exception {} raised!\nMessage: {}", #exception, exception(::agl::log_instance::get_message(message, __VA_ARGS__)).what()); \
		}

	#define AGL_EXCEPTION(exception, message, ...) \
		{ \
			AGL_ASSERT(false, "Exception {} raised!\nMessage: {}", #exception, exception(::agl::log_instance::get_message(message, __VA_ARGS__)).what()); \
		}

	#ifdef AGL_BREAK_ON_ERROR
		#define AGL_CORE_WARNING(message, ...) \
			{ \
				AGL_CORE_ASSERT(false, message, __VA_ARGS__); \
			}

		#define AGL_WARNING(message, ...) \
			{ \
				AGL_ASSERT(false, message, __VA_ARGS__); \
			}
	#else 
		#define AGL_CORE_WARNING(message, ...) \
			{ \
				AGL_CORE_LOG_WARNING(message, __VA_ARGS__); \
			}

		#define AGL_WARNING(message, ...) \
			{ \
				AGL_LOG_WARNING(message, __VA_ARGS__); \
			}
	#endif

#else
	#define AGL_CORE_EXCEPTION(exception, message, ...) \
		{ \
			throw exception((std::string("AGL exception {} raised!") + ::agl::log_instance::get_message(message, #exception, __VA_ARGS__)).c_str()); \
		}

	#define AGL_EXCEPTION(exception, message, ...) \
		{ \
			throw exception(std::string("Exception {} raised!") + ::agl::log_instance::get_message(message, #exception, __VA_ARGS__)); \
		}

	#define AGL_CORE_WARNING(message, ...) \
		{ \
			AGL_CORE_LOG_WARNING(message, __VA_ARGS__); \
		}

	#define AGL_WARNING(message, ...) \
		{ \
			AGL_LOG_WARNING(message, __VA_ARGS__); \
		}
#endif