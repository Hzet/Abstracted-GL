#include "core/app/application.hpp"
#include "graphics/ecs/component/transformable.hpp"
#include "graphics/ecs/component/model.hpp"
#include "graphics/ecs/component/prism.hpp"
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
		static auto meshView = reg.inclusive_view<mesh>();
		static auto modelView = reg.inclusive_view<model>();
		static auto prismView = reg.inclusive_view<prism>();

		if (meshView.needs_update())
			meshView = reg.inclusive_view<mesh>();

		if (modelView.needs_update())
			modelView = reg.inclusive_view<model>();

		if (prismView.needs_update())
			prismView = reg.inclusive_view<prism>();

		for (auto it = meshView.cbegin(); it != meshView.cend(); ++it)
		{
			auto const e = reg.get_entity(*it);
			auto& mesh = reg.get<agl::mesh>(*it);
			mesh.uniforms.send(e);
			
			renderMesh(mesh);
		}
		
		for (auto it = prismView.cbegin(); it != prismView.cend(); ++it)
		{
			auto const e = reg.get_entity(*it);
			auto& prism = reg.get<agl::prism>(*it);

			prism.m_mesh.uniforms.send(e);

			renderMesh(prism.m_mesh);
		}

		for (auto it = modelView.cbegin(); it != modelView.cend(); ++it)
		{
			auto const e = reg.get_entity(*it);
			auto& model = reg.get<agl::model>(*it);

			model.uniforms.send(e);

			for (auto &mesh : model.meshes)
				renderMesh(mesh);
		}
	}
}