#include "core/app/application.hpp"
#include "graphics/ecs/component/transformable.hpp"
#include "graphics/ecs/component/model.hpp"
#include "graphics/ecs/system/render-system.hpp"
#include "graphics/shader/uniform-array.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "system/glcore/gl-core.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	static void renderMesh(const mesh &mesh)
	{
		static auto const& manager = application::get_resource<shader_manager>();
		const auto &s = manager.get_shader(mesh.id_shader);
		s.set_active();

		mesh.rbuffer.bind();

		if (mesh.rbuffer.get_index_count() == 0u)
			AGL_CALL(glDrawArrays(mesh.draw_type, 0u, mesh.rbuffer.get_vertex_count()));
		else
			AGL_CALL(glDrawElements(mesh.draw_type, mesh.rbuffer.get_index_count(), GL_UNSIGNED_INT, 0u));
	}
	
	void render_system::init(registry &reg)
	{

	}

	void render_system::update(registry &reg)
	{
		auto meshView = reg.inclusive_view<mesh>();
		auto modelView = reg.inclusive_view<model>();

		for (auto it = meshView.begin(); it != meshView.end(); ++it)
		{
			const auto e = reg.get_entity(it.get_entity_uid());
		
			(*it).uniforms.send(e);
			
			renderMesh(*it);
		}
				
		for (auto it = modelView.begin(); it != modelView.end(); ++it)
		{
			const auto e = reg.get_entity(it.get_entity_uid());
		
			(*it).uniforms.send(e);

			for (auto &mesh : (*it).meshes)
				renderMesh(mesh);
		}
	}
}