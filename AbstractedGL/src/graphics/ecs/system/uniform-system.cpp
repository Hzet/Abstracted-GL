#include "graphics/ecs/system/uniform-system.hpp"
#include "graphics/shader/uniform-array.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	void uniform_system::init(registry &reg)
	{

	}

	void uniform_system::update(registry &reg)
	{
		static auto view = reg.inclusive_view<uniform_array>();

		if(view.needs_update())
			view = reg.inclusive_view<uniform_array>();

		for (auto it = view.cbegin(); it != view.cend(); ++it)
		{
			auto const e = reg.get_entity(*it);
			auto& uniform = reg.get<uniform_array>(*it);

			uniform.send(e);
		}
	}
}

