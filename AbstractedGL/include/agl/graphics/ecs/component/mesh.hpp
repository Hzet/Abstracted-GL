#pragma once
#include "graphics/render/render-buffer.hpp"
#include "graphics/shader/shader-uid.hpp"
#include "graphics/shader/uniform-array.hpp"
#include "core/enums/gl-draw-type.hpp"

#include <glm/glm.hpp>

namespace agl
{
	class mesh
	{
	public:
		gl_draw_type draw_type;
		shader_uid id_shader;
		render_buffer rbuffer;
		uniform_array uniforms;
	};
}