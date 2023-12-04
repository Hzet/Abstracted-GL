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
		virtual void init(registry &reg) override;
		virtual void update(registry &reg) override;

	private:
		void render_text(entity_uid const& id_entity, registry &reg);

	private:
		mesh m_character_mesh;
	};
}