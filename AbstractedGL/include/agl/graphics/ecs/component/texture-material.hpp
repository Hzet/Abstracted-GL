#pragma once
#include "agl/core/app/application.hpp"
#include "agl/graphics/texture/texture-manager.hpp"

namespace agl
{
	struct texture
	{
		texture_uid ambient;
		texture_uid diffuse;
		texture_uid specular;
	};
}