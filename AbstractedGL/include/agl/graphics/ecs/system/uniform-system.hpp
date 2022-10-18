#pragma once
#include "graphics/ecs/system-group.hpp"
#include "graphics/ecs/component/directional-light.hpp"
#include "utility/ecs/system.hpp"

namespace agl
{
	class uniform_system
		: public system<render_group, uniform_system>
	{
	public:
		static const std::uint64_t s_max_light_count;
		static const directional_light s_directional_light;

		virtual void init(registry &reg) override;
		virtual void update(registry &reg) override;
	};
}