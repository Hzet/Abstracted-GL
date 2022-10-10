#include "core/app/application.hpp"
#include "graphics/shader/uniform-array.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	void uniform_array::send(const entity &e)
	{
		const auto &sig = e.get_signature();

		for (auto i = 0ul; i < m_uniforms.size(); i++)
		{
			if (!sig[m_uniforms[i]->get_component_type_uid()])
				update_uniform(sig, i);

			for (auto &v : m_uniforms[i]->get_shader_uids())
			{
				static const auto& manager = application::get_resource<shader_manager>();
				const auto &s = manager.get_shader(v);
				s.set_active();

				m_uniforms[i]->send(s, e);
			}
		}
	}

	void uniform_array::update_uniform(const signature &sig, std::uint64_t index)
	{
		auto &u = m_uniforms[index];
		const auto &group = group_uniform::get_group(u->get_data_type_uid());

		for(auto i = 0ul; i < group.get_count(); i++)
			if (sig[group[i].get_component_type_uid()])
			{
				u = group.get_uniform(group[i].get_component_type_uid(), u.get());
				break;
			}
	}
}