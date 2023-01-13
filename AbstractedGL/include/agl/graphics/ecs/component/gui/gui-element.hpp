#pragma once
#include <cstdint>
#include "agl/graphics/gui/gui-type.hpp"
#include "agl/graphics/shader/shader-uid.hpp"
#include "agl/ecs/entity.hpp"

namespace agl
{
	struct gui_element
	{
		entity_uid id_mesh;
		shader_uid id_shader;
		gui_type type;
	};
}