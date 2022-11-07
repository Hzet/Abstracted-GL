#pragma once
#include "agl/utility/ecs/system-register.hpp"
#include "agl/graphics/ecs/system-group.hpp"

namespace agl
{
	class gui_system
		: public system_register<render_group, gui_system>
	{
	public:
		virtual void init(registry &reg) override;
		virtual void update(registry &reg) override;
	};
}