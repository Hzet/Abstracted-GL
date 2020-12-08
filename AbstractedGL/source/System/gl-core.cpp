#include "gl-core.hpp"

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
}