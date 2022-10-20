#include "core/app/application.hpp"
#include "graphics/shader/uniform-array.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	void uniform_array::send(const entity &e)
	{
		static const auto& sh_manager = application::get_resource<shader_manager>();
		
		for (auto &uniform : m_uniforms)
		{
			if (!e.has_component(uniform->get_component_type_uid()))
			{
				auto const components = uniform_prototyper::get_prototype_components(uniform->get_type_uid());
				for (auto const index : components)
					if (e.has_component(index))
						uniform = uniform_prototyper::get_prototype(uniform->get_type_uid(), index, uniform.get());
			}

			const auto &s = sh_manager.get_shader(uniform->get_shader_uid());
			s.set_active();

			uniform->send(s, e);
		}
	}
}