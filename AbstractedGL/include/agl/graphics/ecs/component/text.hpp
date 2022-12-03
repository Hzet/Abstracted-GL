#pragma once
#include <string>
#include "agl/graphics/render/render-buffer.hpp"
#include "agl/graphics/text/font-uid.hpp"
#include "agl/graphics/shader/shader-uid.hpp"

namespace agl
{
	struct text
	{
		font_uid id_font;
		shader_uid id_shader;
		std::string text;
	};
}

