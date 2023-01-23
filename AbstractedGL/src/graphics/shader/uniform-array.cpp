#include "agl/core/app/application.hpp"
#include "agl/graphics/shader/uniform-array.hpp"
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/ecs/entity.hpp"

namespace agl
{
	void uniform_array::send(const entity &e)
	{
		static auto& sh_manager = application::get_resource<shader_manager>();
		
		const auto &sig = e.get_signature();

		for (auto i = 0ul; i < m_uniforms.size(); i++)
		{
			AGL_CORE_ASSERT(sig[m_uniforms[i]->get_component_type_uid()], "Entity is missing component {} for uniform {}", component_type_uid::get_name(m_uniforms[i]->get_component_type_uid()), uniform_type_uid::get_name(m_uniforms[i]->get_uniform_type_uid()));

			for (auto const &sh : m_uniforms[i]->get_shader_uids())
			{
				sh_manager.set_active_shader(sh);

				auto const& s = sh_manager.get_active_shader();

				m_uniforms[i]->send(s, e);
			}
		}
	}

	uniform_base& uniform_array::get_uniform(std::uint64_t index)
	{
		return *m_uniforms[index];
	}

	uniform_base const& uniform_array::get_uniform(std::uint64_t index) const
	{
		return *m_uniforms[index];
	}

	std::uint64_t uniform_array::get_count() const
	{
		return m_uniforms.size();
	}
}