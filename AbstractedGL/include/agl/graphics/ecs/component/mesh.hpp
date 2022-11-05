#pragma once
#include "agl/graphics/render/render-buffer.hpp"
#include "agl/graphics/shader/shader-uid.hpp"
#include "agl/core/enums/gl-draw-type.hpp"

#include <glm/glm.hpp>

namespace agl
{
	struct mesh
	{
		gl_draw_type draw_type;
		shader_uid id_shader;
		render_buffer rbuffer;
	};
}