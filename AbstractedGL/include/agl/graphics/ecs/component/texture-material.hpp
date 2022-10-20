#pragma once
#include "graphics/texture/texture-uid.hpp"

namespace agl
{
	struct texture_material
	{
		texture_uid ambient;
		texture_uid diffuse;
		texture_uid specular;
	};
}