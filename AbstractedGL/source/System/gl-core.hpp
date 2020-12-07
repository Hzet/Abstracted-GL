#pragma once 

#include "assert.hpp"

#ifdef AGL_DEBUG
	namespace agl
	{
		void GLClearError();

		bool GLCheckError(std::uint64_t value);

		std::uint64_t GLGetLastError();

		void GLDebugMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, const char* message, const void* userParam);
	}

	#define AGL_CALL(call) \
		do { \
			agl::GLClearError(); \
			call; \
			AGL_CORE_ASSERT(agl::GLCheckError(agl::GLGetLastError()), "Failed to execute OpenGL call!\n", "Error code: [", agl::GLGetLastError(), "]\n"); \
		} while(false)

	#define AGL_GL_DEBUG_SETUP(severity) \
		glEnable(GL_DEBUG_OUTPUT); \
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); \
		glDebugMessageCallback(GLDebugMessageCallback, nullptr); \
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, severity, 0, NULL, GL_FALSE);

#else
	#define AGL_CALL(call) call
#endif