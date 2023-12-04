#include "agl/system/glcore/gl-core.hpp"

namespace agl
{
	static std::uint64_t LastGLError = GL_NO_ERROR;

	void gl_clear_error()
	{
		auto error = glGetError();

		if (error == GL_NO_ERROR)
			LastGLError = GL_NO_ERROR;
		else
			while ((error = glGetError()) != GL_NO_ERROR)
				LastGLError = error;
	}

	bool gl_check_error(std::uint64_t value)
	{
		return value == GL_NO_ERROR;
	}

	std::uint64_t gl_get_last_error()
	{
		return LastGLError;
	}
}