#include "gl-core.hpp"
#include <glad/glad.h>

namespace agl
{
	static std::uint64_t LastGLError = GL_NO_ERROR;

	void GLClearError()
	{
		std::uint64_t error = glGetError();

		if (error == GL_NO_ERROR)
			LastGLError = GL_NO_ERROR;
		else
			while ((error = glGetError()) != GL_NO_ERROR)
				LastGLError = error;
	}

	bool GLCheckError(std::uint64_t value)
	{
		return value == GL_NO_ERROR;
	}

	std::uint64_t GLGetLastError()
	{
		return LastGLError;
	}

	void GLDebugMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, const char* message, const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         AGL_CORE_LOG_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       AGL_CORE_LOG_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          AGL_CORE_LOG_WARNING(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: AGL_CORE_LOG_TRACE(message); return;
		}

		AGL_CORE_ASSERT(false, "Unknown severity level!");
	}
}