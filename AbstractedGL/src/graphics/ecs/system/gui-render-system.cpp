#include "agl/core/app/application.hpp"
#include "agl/graphics/ecs/component/text.hpp"
#include "agl/graphics/ecs/system/gui-render-system.hpp"
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/graphics/shader/uniform-array.hpp"
#include "agl/graphics/text/font-manager.hpp"
#include "agl/graphics/texture/texture-manager.hpp"
#include "agl/ecs/ecs.hpp"

namespace agl
{
	void gui_render_system::init(registry &reg)
	{
		m_character_mesh.draw_type = DRAW_TRIANGLES;

		auto positions = std::vector<glm::vec4>(6);
		auto texture_positions = std::vector<glm::vec2>{
			{ 0.f, 0.f }, // bottom left
			{ 0.f, 1.f }, // top left
			{ 1.f, 0.f }, // bottom right

			{ 0.f, 1.f }, // top left
			{ 1.f, 1.f }, // top right
			{ 1.f, 0.f } // bottom right
		};

		m_character_mesh.rbuffer.set_usage(BUFFER_DYNAMIC_DRAW);
		m_character_mesh.rbuffer.push_vertices<position>(positions.cbegin(), positions.cend());
		m_character_mesh.rbuffer.push_vertices<texture_position>(texture_positions.cbegin(), texture_positions.cend());
	}

	void gui_render_system::update(registry &reg)
	{
		static auto text_view = reg.inclusive_view<agl::text>();
		if (text_view.needs_update())
			text_view = reg.inclusive_view<agl::text>();

		for (auto it = text_view.cbegin(); it != text_view.cend(); ++it)
			render_text(*it, reg);
	}

	void gui_render_system::render_text(entity_uid const& id_entity, registry &reg)
	{
		static auto& shader_manager = application::get_resource<agl::shader_manager>();
		static auto& texture_manager = application::get_resource<agl::texture_manager>();
		static auto const& font_manager = application::get_resource<agl::font_manager>();

		auto const& text_entity = reg.get_entity(id_entity);
		auto const& text = reg.get<agl::text>(id_entity);
		auto const& font = font_manager.get_font(text.id_font);

		if (text_entity.has_component<uniform_array>())
		{
			auto& uniforms = reg.get<uniform_array>(id_entity);
			uniforms.send(text_entity);
		}

		shader_manager.set_active_shader(text.id_shader);

		auto w = float{};
		auto h = float{};
		auto x = float{};
		auto y = float{};
		auto offset = float{};

		for (auto const ch : text.text)
		{
			auto const& glyph = font.get_glyph(ch);

			w = glyph.texture.get_size().x;
			h = glyph.texture.get_size().y;
			x = offset + glyph.bearing.x;
			y = glyph.bearing.y - glyph.texture.get_size().y;

			m_character_mesh.rbuffer.get<position>(0) = { x, y + h, 0.f };     // bottom left
			m_character_mesh.rbuffer.get<position>(1) = { x, y, 0.f };         // top left
			m_character_mesh.rbuffer.get<position>(2) = { x + w, y + h, 0.f }; // bottom right
			
			m_character_mesh.rbuffer.get<position>(3) = { x, y, 0.f };         // top left
			m_character_mesh.rbuffer.get<position>(4) = { x + w, y, 0.f };     // top right
			m_character_mesh.rbuffer.get<position>(5) = { x + w, y + h, 0.f }; // bottom right
			
			m_character_mesh.rbuffer.update_buffers();
			
			glyph.texture.bind();
			shader_manager.get_shader(text.id_shader).set_uniform(shader_manager.get_shader(text.id_shader).ask_location("id_texture"), 0);

			m_character_mesh.rbuffer.bind();

			AGL_CALL(glDrawArrays(m_character_mesh.draw_type, 0u, m_character_mesh.rbuffer.get_vertex_count()));

			m_character_mesh.rbuffer.unbind();

			offset += glyph.advance >> 6;
		}
	}
}