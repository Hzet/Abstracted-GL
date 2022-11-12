#include "agl/core/app/application.hpp"
#include "agl/graphics/ecs/component/renderable.hpp"
#include "agl/graphics/ecs/component/model.hpp"
#include "agl/graphics/ecs/system/render-system.hpp"
#include "agl/graphics/shader/uniform-array.hpp"
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/system/glcore/gl-core.hpp"
#include "agl/utility/ecs/entity.hpp"

namespace agl
{
	void render_system::init(registry &reg)
	{

	}

	void render_system::update(registry &reg)
	{
		static auto renderable_view = reg.inclusive_view<renderable>();

		if (renderable_view.needs_update())
			renderable_view = reg.inclusive_view<renderable>();

		static auto const& manager = application::get_resource<shader_manager>();
		
		for (auto it = renderable_view.cbegin(); it != renderable_view.cend(); ++it)
		{
			auto const& renderable = reg.get<agl::renderable>(*it);
			auto const e = reg.get_entity(*it);
			auto& mesh = reg.get<agl::mesh>(renderable.id_renderable);

			if (e.has_component<agl::uniform_array>())
			{
				auto& uniforms = reg.get<uniform_array>(*it);
				uniforms.send(e);
			}

			const auto &s = manager.get_shader(renderable.id_shader);
			s.set_active();

			if (mesh.rbuffer.require_update())
				mesh.rbuffer.update_buffers();

			mesh.rbuffer.bind();

			if (mesh.rbuffer.get_index_count() == 0u)
				AGL_CALL(glDrawArrays(mesh.draw_type, 0u, mesh.rbuffer.get_vertex_count()));
			else
				AGL_CALL(glDrawElements(mesh.draw_type, mesh.rbuffer.get_index_count(), GL_UNSIGNED_INT, 0u));

			mesh.rbuffer.unbind();
		}
	}
}