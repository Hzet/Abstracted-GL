#include "agl/core/app/application.hpp"
#include "agl/graphics/ecs/component/text.hpp"
#include "agl/graphics/ecs/component/gui/gui-element.hpp"
#include "agl/graphics/ecs/system/gui-render-system.hpp"
#include "agl/graphics/ecs/system/render-system.hpp"
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/graphics/shader/uniform-array.hpp"
#include "agl/graphics/text/font-manager.hpp"
#include "agl/graphics/texture/texture-manager.hpp"
#include "agl/ecs/ecs.hpp"

namespace agl
{
	void gui_render_system::init(registry &reg)
	{
	}

	void gui_render_system::update(registry &reg)
	{
		static auto gui_element_view = reg.inclusive_view<gui_element>();
		static auto& sh_manager = application::get_resource<shader_manager>();

		if (gui_element_view.needs_update())
			gui_element_view = reg.inclusive_view<gui_element>();

		for (auto it = gui_element_view.cbegin(); it != gui_element_view.cend(); ++it)
		{
			auto gui_entity = reg.get_entity(*it);
			auto const& gui_element = reg.get<agl::gui_element>(*it);

			if (gui_entity.has_component<uniform_array>())
			{
				auto& uniforms = reg.get<uniform_array>(*it);
				uniforms.send(gui_entity);
			}

			if (gui_element.id_mesh != entity_uid::INVALID)
			{
				sh_manager.set_active_shader(gui_element.id_shader);
				render_system::render_mesh(gui_element.id_mesh, reg);
			}

			if (gui_entity.has_component<text>())
				render_text(*it, reg);
		}
	}

	void gui_render_system::render_text(entity_uid const& id_text, registry &reg)
	{
		static auto& shader_manager = application::get_resource<agl::shader_manager>();
		static auto& texture_manager = application::get_resource<agl::texture_manager>();
		static auto const& font_manager = application::get_resource<agl::font_manager>();

		auto const& text_entity = reg.get_entity(id_text);
		auto const& text = reg.get<agl::text>(id_text);
		auto const& font = font_manager.get_font(text.id_font);

		auto character_mesh = mesh{};

		character_mesh.draw_type = DRAW_TRIANGLES;

		auto positions = std::vector<glm::vec2>(6);
		auto texture_positions = std::vector<glm::vec2>{
			{ 0.f, 0.f }, // bottom left
			{ 0.f, 1.f }, // top left
			{ 1.f, 0.f }, // bottom right

			{ 0.f, 1.f }, // top left
			{ 1.f, 1.f }, // top right
			{ 1.f, 0.f } // bottom right
		};

		character_mesh.rbuffer.set_usage(BUFFER_DYNAMIC_DRAW);
		character_mesh.rbuffer.push_vertices<position_2d>(positions.cbegin(), positions.cend());
		character_mesh.rbuffer.push_vertices<texture_position>(texture_positions.cbegin(), texture_positions.cend());

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

			character_mesh.rbuffer.get<position_2d>(0) = { x, y + h };     // bottom left
			character_mesh.rbuffer.get<position_2d>(1) = { x, y };         // top left
			character_mesh.rbuffer.get<position_2d>(2) = { x + w, y + h }; // bottom right
												
			character_mesh.rbuffer.get<position_2d>(3) = { x, y };         // top left
			character_mesh.rbuffer.get<position_2d>(4) = { x + w, y };     // top right
			character_mesh.rbuffer.get<position_2d>(5) = { x + w, y + h }; // bottom right
			
			character_mesh.rbuffer.update_buffers();
			
			glyph.texture.bind();
			shader_manager.get_shader(text.id_shader).set_uniform(shader_manager.get_shader(text.id_shader).ask_location("id_texture"), 0);

			character_mesh.rbuffer.bind();

			AGL_CALL(glDrawArrays(character_mesh.draw_type, 0u, character_mesh.rbuffer.get_vertex_count()));

			character_mesh.rbuffer.unbind();

			offset += glyph.advance >> 6;
		}
	}
}