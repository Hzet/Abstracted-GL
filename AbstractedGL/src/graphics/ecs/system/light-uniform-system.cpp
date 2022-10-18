#include "graphics/ecs/system/light-uniform-system.hpp"
#include "graphics/ecs/component/uniform/spot-light.hpp"
#include "core/app/application.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	void light_uniform_system::init(registry &reg)
	{

	}

	void light_uniform_system::update(registry &reg)
	{
		auto const& sh_manager = application::get_resource<shader_manager>();
		static auto spot_view = reg.inclusive_view<uniform<spot_light>>();
		auto reindex_spot_view = true;
		auto index = 0;

		if (spot_view.needs_update())
		{
			spot_view = reg.inclusive_view<uniform<spot_light>>();
			reindex_spot_view = true;
		}

		for (auto it = spot_view.begin(); it != spot_view.end(); ++it)
		{
			auto const e = reg.get_entity(*it);
			auto& light = reg.get<uniform<spot_light>>(*it);

			if (reindex_spot_view)
				light.set_name(light.get_name(), index++);

			const auto &s = sh_manager.get_shader(light.get_shader_uid());
			s.set_active();

			light.send(s, e);
		}

		reindex_spot_view = false;
	}
}

