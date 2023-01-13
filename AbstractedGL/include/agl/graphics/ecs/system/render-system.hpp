#pragma once
#include "agl/ecs/system-register.hpp"
#include "agl/graphics/ecs/system-group.hpp"

namespace agl
{
	class render_system
		: public system_register<render_group, render_system>
	{
	public:
		static void render_mesh(entity_uid const& id_mesh, registry &reg);

	public:
		virtual void init(registry &reg) override;
		virtual void update(registry &reg) override;
	};
}