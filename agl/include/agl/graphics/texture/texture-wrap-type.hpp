#pragma once
#include <cstdint>
#include <glad/glad.h>


namespace agl
{
	enum texture_wrap_type : std::uint32_t
	{
		TEXTURE_WRAP_NONE = 0,
		TEXTURE_WRAP_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		TEXTURE_WRAP_CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
		TEXTURE_WRAP_MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		TEXTURE_WRAP_REPEAT = GL_REPEAT
	};
}

