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

		for (auto it = view.begin(); it != view.end(); ++it)
		{
			const auto e = reg.get_entity(it.get_entity_uid());

			(*it).send(e);
		}
	}
}

