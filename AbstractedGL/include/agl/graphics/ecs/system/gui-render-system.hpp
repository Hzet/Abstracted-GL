#pragma once
#include "agl/ecs/system-register.hpp"
#include "agl/graphics/ecs/system-group.hpp"
#include "agl/graphics/ecs/component/mesh.hpp"

namespace agl
{
	class gui_render_system
		: public system_register<render_group, gui_render_system>
	{
	public:
		static void render_text(entity_uid const& id_entity, registry &reg);

	public:
		virtual void init(registry &reg) override;
		virtual void update(registry &reg) override;

	private:
		mesh m_character_mesh;
	};
}