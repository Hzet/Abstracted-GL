#pragma once
#include "utility/ecs/system.hpp"
#include "graphics/ecs/system-group.hpp"

namespace agl
{
	class camera_system
		: public system<simulation_group, camera_system>
	{
	public:
		virtual void init(registry &reg) override;
		virtual void update(registry &reg) override;
	};
}