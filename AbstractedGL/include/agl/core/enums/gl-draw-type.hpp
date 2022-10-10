#pragma once
#include <cstdint>
#include <glad/glad.h>

namespace agl
{
	enum gl_draw_type : std::uint32_t
	{
		DRAW_POINTS = GL_POINTS,
		DRAW_LINE_STRIP = GL_LINE_STRIP,
		DRAW_LINE_LOOP = GL_LINE_LOOP,
		DRAW_LINES = GL_LINES,
		DRAW_LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
		DRAW_LINES_ADJACENCY = GL_LINES_ADJACENCY,
		DRAW_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		DRAW_TRIANGLE_FAN = GL_TRIANGLE_FAN,
		DRAW_TRIANGLES = GL_TRIANGLES,
		DRAW_TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
		DRAW_TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
		DRAW_PATCHES = GL_PATCHES
	};
}

