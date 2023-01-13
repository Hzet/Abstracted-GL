#include "agl/core/app/application.hpp"
#include "agl/graphics/ecs/component/renderable.hpp"
#include "agl/graphics/ecs/component/mesh.hpp"
#include "agl/graphics/ecs/system/render-system.hpp"
#include "agl/graphics/shader/uniform-array.hpp"
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/graphics/texture/texture-manager.hpp"
#include "agl/system/glcore/gl-core.hpp"
#include "agl/ecs/entity.hpp"

#include <agl/graphics/types/types.hpp>
namespace agl
{
	void render_system::render_mesh(entity_uid const& id_mesh, registry &reg)
	{
		auto& mesh = reg.get<agl::mesh>(id_mesh);

		if (mesh.rbuffer.require_update())
			mesh.rbuffer.update_buffers();

		mesh.rbuffer.bind();

		//for (auto i = 0; i < mesh.rbuffer.get_vertex_count(); ++i)
		//{
		//	AGL_CORE_LOG_INFO("pos: {{}, {}, {}}", mesh.rbuffer.get<position>(i).x, mesh.rbuffer.get<position>(i).y, mesh.rbuffer.get<position>(i).z);
		////	AGL_CORE_LOG_INFO("col: {{}, {}, {}}", mesh.rbuffer.get<color>(i).x, mesh.rbuffer.get<color>(i).y, mesh.rbuffer.get<color>(i).z);
		//}

		if (mesh.rbuffer.get_index_count() == 0u)
			AGL_CALL(glDrawArrays(mesh.draw_type, 0u, mesh.rbuffer.get_vertex_count()));
		else
			AGL_CALL(glDrawElements(mesh.draw_type, mesh.rbuffer.get_index_count(), GL_UNSIGNED_INT, 0u));

		mesh.rbuffer.unbind();
	}


	void render_system::init(registry &reg)
	{
	}

	void render_system::update(registry &reg)
	{
		static auto& manager = application::get_resource<shader_manager>();
		static auto& shader_manager = application::get_resource<agl::shader_manager>();
		static auto& texture_manager = application::get_resource<agl::texture_manager>();
		static auto renderable_view = reg.inclusive_view<renderable>();

		if (renderable_view.needs_update())
			renderable_view = reg.inclusive_view<renderable>();

		for (auto it = renderable_view.cbegin(); it != renderable_view.cend(); ++it)
		{
			auto const& e = reg.get_entity(*it);
			
			if (e.has_component<agl::uniform_array>())
			{
				auto& uniforms = reg.get<uniform_array>(*it);
				uniforms.send(e);
			}

			auto const& renderable = reg.get<agl::renderable>(*it);

			shader_manager.set_active_shader(renderable.id_shader);

			render_mesh(renderable.id_renderable, reg);
			texture_manager.unbind_textures();
		}
	}
}