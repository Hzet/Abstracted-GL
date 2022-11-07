#pragma once
#include "agl/utility/ecs/system-register.hpp"
#include "agl/graphics/ecs/system-group.hpp"

namespace agl
{
	class light_system
		: public system_register<simulation_group, light_system>
	{
	public:
		virtual void init(registry &reg) override;
		virtual void update(registry &reg) override;
	};
}