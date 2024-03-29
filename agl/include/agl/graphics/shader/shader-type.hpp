#pragma once
#include <cstdint>
#include <glad/glad.h>

namespace agl
{
	enum shader_type : std::uint64_t
	{
		SHADER_INVALID = 0,
		SHADER_VERTEX = GL_VERTEX_SHADER,
		SHADER_TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		SHADER_TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
	    SHADER_GEOMETRY = GL_GEOMETRY_SHADER,
		SHADER_FRAGMENT = GL_FRAGMENT_SHADER,
		SHADER_COMPUTE = GL_COMPUTE_SHADER,
	};
}

