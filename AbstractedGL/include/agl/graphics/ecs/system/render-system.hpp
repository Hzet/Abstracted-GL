#pragma once
#include "agl/utility/ecs/system.hpp"
#include "agl/graphics/ecs/system-group.hpp"

namespace agl
{
	class render_system
		: public system<render_group, render_system>
	{
	public:
		virtual void init(registry &reg) override;
		virtual void update(registry &reg) override;
	};
}