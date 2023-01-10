#pragma once
#include "agl/graphics/shader/shader-uid.hpp"
#include "agl/ecs/entity-uid.hpp"

namespace agl
{
	struct renderable
	{
		entity_uid id_renderable;
		shader_uid id_shader;
	};
}