#pragma once
#include "agl/graphics/texture/texture2d.hpp"

namespace agl
{
	struct glyph
	{
		std::uint64_t advance;
		glm::vec2 bearing;
		char character;
		texture_2d texture;
	};
}