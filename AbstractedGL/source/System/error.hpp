#pragma once 

#include "exception.hpp"
#include "log.hpp"

#define AGL_CRITICAL_ERROR_IMPL(condition, tag, message, ...) \
	do { \
		if(!condition) \
		{ \
			AGL_ERROR_LOG_TAGGED(tag, "Critical error on: ", #condition, message, __VA_ARGS__); \
			throw agl::exception::CException(message); \
		} \
	} while(false) \

#define AGL_CRITICALL_ERROR_CORE(condition, message, ...) AGL_CRITICAL_ERROR_IMPL(condition, "CRITICAL CORE ERROR", message, __VA_ARGS__);

#define AGL_CRITICAL_ERROR(condition, message, ...) AGL_CRITICAL_ERROR_IMPL(condition, "CRITICAL ERROR", message, __VA_ARGS__);