#include "agl/graphics/ecs/system/light-system.hpp"
#include "agl/graphics/ecs/component/direction.hpp"
#include "agl/graphics/ecs/component/directional-light.hpp"
#include "agl/graphics/ecs/component/spot-light.hpp"
#include "agl/graphics/ecs/component/transformable.hpp"
#include "agl/graphics/ecs/component/uniform/spot-light.hpp"
#include "agl/graphics/shader/uniform-array.hpp"	

#include "agl/core/app/application.hpp"

namespace agl
{
	void light_system::init(registry &reg)
	{

	}

	void light_system::update(registry &reg)
	{
		//static auto spot_light_view = reg.inclusive_view<spot_light, transformable, direction>();
		//static auto directional_light_view = reg.inclusive_view<directional_light, transformable, direction>();
		//auto reindex_spot_light = bool{};
		//auto index = 0;
		//
		//if (spot_light_view.needs_update())
		//{
		//	spot_light_view = reg.inclusive_view<spot_light, transformable, direction>();
		//	reindex_spot_light = true;
		//}
		//else
		//	reindex_spot_light = false;
		//
		//if (directional_light_view.needs_update())
		//	directional_light_view = reg.inclusive_view<directional_light, transformable, direction>();
		//
		//static auto const& sh_manager = agl::application::get_resource<agl::shader_manager>();
		//static auto& shader = sh_manager.get_shader(sh_manager.get_shader_uid(0));
		//
		//static auto location = shader.get_location("spot_light_active_count");
		//shader.set_uniform(location, static_cast<std::int32_t>(spot_light_view.get_count()));
		//
		//for (auto it = spot_light_view.cbegin(); it != spot_light_view.cend(); ++it)
		//{
		//	auto const& e = reg.get_entity(*it);
		//	auto& light = reg.get<spot_light>(*it);
		//	auto& uniforms = reg.get<uniform_array>(*it);
		//
		//	if (reindex_spot_light)
		//	{
		//		auto& light_uniform = uniforms.get_uniform<spot_light_uniform>();
		//		light_uniform.set_name(light_uniform.get_name(), index++);
		//
		//		for (int i = 0; i < uniforms.get_count(); ++i)
		//			uniforms.get_uniform(i).set_name(light_uniform.get_full_name());
		//	}
		//
		//	uniforms.send(e);
		//}
	}
}