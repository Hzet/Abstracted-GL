#include "core/app/application.hpp"
#include "graphics/shader/uniform-array.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	void uniform_array::send(const entity &e)
	{
		static const auto& sh_manager = application::get_resource<shader_manager>();
		
		const auto &sig = e.get_signature();

		for (auto i = 0ul; i < m_uniforms.size(); i++)
		{
			AGL_CORE_ASSERT(sig[m_uniforms[i]->get_component_type_uid()], "Entity is missing component {} for uniform {}", component_type_uid::get_name(m_uniforms[i]->get_component_type_uid()), uniform_type_uid::get_name(m_uniforms[i]->get_data_type_uid()));

			const auto &s = sh_manager.get_shader(m_uniforms[i]->get_shader_uid());
			s.set_active();

			m_uniforms[i]->send(s, e);
		}
	}
}