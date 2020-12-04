#pragma once 

#include "assert.hpp"

namespace agl
{
	void OpenGLClearError();

	bool OpenGLCheckError(std::uint64_t value);

	std::uint64_t OpenGLGetError();
}

#define AGL_GLCall(call) \
	do { \
		agl::OpenGLClearError(); \
		call; \
		std::uint64_t error = agl::OpenGLGetError();
		AGL_CORE_ASSERT(agl::OpenGLCheckError(error), "Failed to execute OpenGL call!\n", "Error code: [", error, "]\n"); \
	} while(false) \