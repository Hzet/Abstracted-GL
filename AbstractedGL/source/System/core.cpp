#include "core.hpp"
#include <glad/glad.h>

namespace agl
{

	void OpenGLClearError()
	{
		std::uint64_t error;
		do {
			error = glGetError();
		} while (error != GL_NO_ERROR);
	}

	bool OpenGLCheckError(std::uint64_t value)
	{
		return value == GL_NO_ERROR;
	}

	std::uint64_t OpenGLGetError()
	{
		return glGetError();
	}

}