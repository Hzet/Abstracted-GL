#pragma once 

#include "assert.hpp"

#include <glad/glad.h>

#ifdef AGL_DEBUG
	namespace agl
	{
		void GLClearError();

		bool GLCheckError(std::uint64_t value);

		std::uint64_t GLGetLastError();
	}

	#define AGL_CALL(call) \
		do { \
			::agl::GLClearError(); \
			call; \
			AGL_CORE_ASSERT(::agl::GLCheckError(::agl::GLGetLastError()), "Failed to execute OpenGL call!\n", "Error code: [", ::agl::GLGetLastError(), "]\n"); \
		} while(false)
#else
	#define AGL_CALL(call) call
#endif