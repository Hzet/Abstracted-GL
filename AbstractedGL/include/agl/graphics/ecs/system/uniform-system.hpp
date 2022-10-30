#pragma once
#include "utility/ecs/system.hpp"
#include "graphics/ecs/system-group.hpp"

namespace agl
{
	class uniform_system
		: public system<render_group, uniform_system>
	{
	public:
		virtual void init(registry &reg) override;
		virtual void update(registry &reg) override;
	};
}