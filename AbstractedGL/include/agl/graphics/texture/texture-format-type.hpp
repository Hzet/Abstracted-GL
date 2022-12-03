#pragma once
#include <cstdio>
#include <glad/glad.h>

namespace agl
{
	enum texture_format_type : std::uint32_t
	{
		TEXTURE_FORMAT_RED = GL_RED,
		TEXTURE_FORMAT_RG = GL_RG, 
		TEXTURE_FORMAT_RGB = GL_RGB, 
		TEXTURE_FORMAT_RGBA = GL_RGBA, 
		TEXTURE_FORMAT_STENCIL = GL_STENCIL_INDEX,
		TEXTURE_FORMAT_DEPTH = GL_DEPTH_COMPONENT,
		TEXTURE_FORMAT_DEPTH_STENCIL = GL_DEPTH_STENCIL
	};
}

