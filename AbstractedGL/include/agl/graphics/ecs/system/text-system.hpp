#pragma once
#include "agl/utility/ecs/system-register.hpp"
#include "agl/graphics/ecs/system-group.hpp"
#include "agl/graphics/ecs/component/mesh.hpp"

namespace agl
{
	class text_system
		: public system_register<render_group, text_system>
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