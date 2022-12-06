#include "agl/core/app/input.hpp"
#include "agl/core/app/layer-manager.hpp"
#include "agl/graphics/shader/uniform-array.hpp"
#include "agl/graphics/ecs/component/uniform/camera.hpp"
#include "agl/graphics/ecs/component/uniform/position.hpp"
#include "agl/graphics/ecs/component/uniform/transform.hpp"
#include "agl/graphics/ecs/component/uniform/material.hpp"
#include "agl/graphics/ecs/component/uniform/texture-material.hpp"
#include "agl/graphics/ecs/component/renderable.hpp"
#include "agl/graphics/ecs/component/text.hpp"
#include "agl/graphics/ecs/component/mesh.hpp"
#include "agl/graphics/shape/rectangle.hpp"
#include "agl/graphics/shape/prism.hpp"
#include "agl/graphics/texture/texture-manager.hpp"
#include "agl/graphics/text/font-manager.hpp"
#include "scene-layer.hpp"

namespace editor
{
	void scene_layer::on_attach()
	{
		m_frame_count = 0;

		auto& reg = agl::application::get_resource<agl::registry>();
		auto& sh_manager = agl::application::get_resource<agl::shader_manager>();
		auto& texture_manager = agl::application::get_resource<agl::texture_manager>();
		auto& font_manager = agl::application::get_resource<agl::font_manager>();

		// load shaders
		auto const id_basic_shader = sh_manager.load_from_file("resource/basic-vertex.glsl", "resource/basic-fragment.glsl");
		auto const id_light_shader = sh_manager.load_from_file("resource/light.vsh", "resource/light.fsh");
		auto const id_text_shader = sh_manager.load_from_file("resource/text-vertex.glsl", "resource/text-fragment.glsl");
		sh_manager.link_all_shaders();

		// load fonts 
		auto const id_bahnschrift_font = font_manager.load_from_file("resource/bahnschrift.ttf", 48);

		// camera orthographic
		m_camera_orthographic = reg.create();
		{
			auto& camera = m_camera_orthographic.attach_component<agl::camera_orthographic>();
			auto& camera_transform = m_camera_orthographic.attach_component<agl::transformable>();
			auto& camera_direction = m_camera_orthographic.attach_component<agl::direction>(agl::camera_base::s_world_direction);
			auto& uniforms = m_camera_orthographic.attach_component<agl::uniform_array>();

			camera.set_resolution(agl::application::get_instance().get_window().get_data().resolution);
			camera.set_planes({ -1.f, 1.f });

			uniforms.add_uniform<agl::camera_uniform, agl::camera_orthographic>(id_text_shader);
		}

		// camera perspective
		m_camera_velocity = 40.f;
		m_camera_sensitivity = 0.3f;

		{
			m_camera_perspective = reg.create();
		
			auto& camera = m_camera_perspective.attach_component<agl::camera_perspective>();
			auto& camera_transform = m_camera_perspective.attach_component<agl::transformable>();
			auto& camera_direction = m_camera_perspective.attach_component<agl::direction>(agl::camera_base::s_world_direction);
			auto& uniforms = m_camera_perspective.attach_component<agl::uniform_array>();

			camera.set_resolution(agl::application::get_instance().get_window().get_data().resolution);
			camera.set_planes({ 0.1f, 100000.f });
			camera.set_fov(60.f);
			camera.look_at({ 0.f, 0.f, 0.f });

			camera_transform.set_position({ 0.f, 0.f, 0.f });

			uniforms.add_uniform<agl::camera_uniform, agl::camera_perspective>(id_basic_shader);
		}

		// mesh 
		auto empty_texture_uid = texture_manager.load_from_file("resource/empty-texture.png");

		{
			auto prism_entity = reg.create();
			auto prism_builder = agl::prism_builder{ 4, glm::sqrt(5.f) / 2.f, 2.5f };

			auto const prism_positions = prism_builder.get_positions();
			auto const prism_colors = prism_builder.get_colors(agl::color{ 0.f, 1.f, 0.f, 1.f });
			auto const prism_indices = prism_builder.get_indices();

			auto& prism_mesh = prism_entity.attach_component<agl::mesh>();
			prism_mesh.draw_type = prism_builder.get_draw_type();
			prism_mesh.rbuffer.push_indices(prism_indices.cbegin(), prism_indices.cend());
			prism_mesh.rbuffer.push_vertices<agl::position>(prism_positions.cbegin(), prism_positions.cend());
			prism_mesh.rbuffer.push_vertices<agl::color>(prism_colors.cbegin(), prism_colors.cend());
			
			//for (auto i = 0; i < prism_positions.size(); ++i)
			//	AGL_CORE_LOG_INFO("{{}, {}, {}}", prism_positions[i]->x / 1280.f, prism_positions[i]->y / 1024.f, prism_positions[i]->z);

			for (auto i = 0; i < 1000; ++i)
			{
				auto renderable = agl::renderable{ prism_entity.get_entity_uid(), id_basic_shader };

				auto e = reg.create();
				auto& transform = e.attach_component<agl::transformable>();
				auto& material = e.attach_component<agl::material>();
				e.attach_component<agl::renderable>(renderable);
				e.attach_component<agl::texture>(empty_texture_uid);

				auto& uniforms = e.attach_component<agl::uniform_array>();
				uniforms.add_uniform<agl::transform_uniform, agl::transformable>(id_basic_shader);
				uniforms.add_uniform<agl::texture_uniform, agl::texture>(id_basic_shader);
				//uniforms.add_uniform<agl::material_uniform, agl::material>(basic_shader);

				material.ambient = glm::vec4{ 0.f };
				material.diffuse = glm::vec4{ 1.0f, 1.0f, 0.31f, 1.f };
				material.specular = glm::vec4{ 1.f };
				material.shininess = 32.f;

				transform.set_position(glm::sphericalRand(50.f));
			}
		}

		// rectangle 
		{
			auto rect_texture_uid = texture_manager.load_from_file("resource/container.jpg");
			auto rect_entity = reg.create();
		//	rect_entity.attach_component<agl::renderable>(rect_entity, id_basic_shader);
			rect_entity.attach_component<agl::texture>(rect_texture_uid);
			auto& rect_mesh = rect_entity.attach_component<agl::mesh>();
			auto& rect_transform = rect_entity.attach_component<agl::transformable>();
			auto& rect_uniforms = rect_entity.attach_component<agl::uniform_array>();

			auto rect_builder = agl::rectangle_builder{ agl::rectangle{{10.f, 20.f}} };
			auto const rect_indices = rect_builder.get_indices();
			auto const rect_positions = rect_builder.get_positions();
			auto const rect_colors = rect_builder.get_colors(agl::color{ 1.f, 1.f, 1.f, 1.f });
			auto const rect_texture = std::vector<agl::texture_position>{
				{0.f, 0.f}, // bottom left,
				{0.f, 1.f}, // top left,
				{1.f, 1.f}, // top right,
				{1.f, 0.f}  // bottom right
			};
			rect_mesh.draw_type = rect_builder.get_draw_type();
			rect_mesh.rbuffer.push_indices(rect_indices.cbegin(), rect_indices.cend());
			rect_mesh.rbuffer.push_vertices<agl::position>(rect_positions.cbegin(), rect_positions.cend());
			rect_mesh.rbuffer.push_vertices<agl::color>(rect_colors.cbegin(), rect_colors.cend());
			rect_mesh.rbuffer.push_vertices<agl::texture_position>(rect_texture.cbegin(), rect_texture.cend());

			rect_uniforms.add_uniform<agl::transform_uniform, agl::transformable>(id_basic_shader);
			rect_uniforms.add_uniform<agl::texture_uniform, agl::texture>(id_basic_shader);
		}

		// fps text
		m_fps_text = reg.create();

		{
			auto& text = m_fps_text.attach_component<agl::text>(id_bahnschrift_font, id_text_shader, "0.0");
			auto& transform = m_fps_text.attach_component<agl::transformable>();
			auto& uniforms = m_fps_text.attach_component<agl::uniform_array>();

			transform.set_position({-0.98f, 0.95f, 0.f});

			uniforms.add_uniform<agl::transform_uniform, agl::transformable>(id_text_shader);
		}
	}

	void scene_layer::on_update()
	{
		auto frame_time = m_timer.elapsed().seconds();
		m_timer.reset();
		++m_frame_count;

		auto e = agl::event{};
		while (agl::application::get_instance().get_window().poll_event(e))
		{
			switch (e.type)
			{
			case agl::WINDOW_CLOSED:
				agl::application::get_instance().shutdown();
				return;
			}
		}

		if (agl::input::key_pressed(agl::ESCAPE))
		{
			agl::application::get_instance().shutdown();
			return;
		}
		if (agl::input::key_pressed(agl::A))
		{
			m_camera_perspective.get_component<agl::transformable>().move(m_camera_perspective.get_component<agl::direction>().right * -m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::D))
		{
			m_camera_perspective.get_component<agl::transformable>().move(m_camera_perspective.get_component<agl::direction>().right * m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::W))
		{
			m_camera_perspective.get_component<agl::transformable>().move(m_camera_perspective.get_component<agl::direction>().forward * m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::S))
		{
			m_camera_perspective.get_component<agl::transformable>().move(m_camera_perspective.get_component<agl::direction>().forward * -m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::LEFT_CONTROL))
		{
			m_camera_perspective.get_component<agl::transformable>().move(m_camera_perspective.get_component<agl::direction>().up * -m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::SPACE))
		{
			m_camera_perspective.get_component<agl::transformable>().move(m_camera_perspective.get_component<agl::direction>().up * m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::P))
		{
			m_camera_perspective.get_component<agl::camera_perspective>().look_at({ 0,0,0 });
		}
		if (agl::input::key_pressed(agl::E))
		{
			m_camera_perspective.get_component<agl::transformable>().rotate(glm::vec3{ 0.f, 0.f, -5.f });
		}
		if (agl::input::key_pressed(agl::Q))
		{
			m_camera_perspective.get_component<agl::transformable>().rotate(glm::vec3{ 0.f, 0.f, 5.f });
		}

		auto const curr_mouse_pos = agl::input::get_mouse_position();
		auto const mouse_pos_offset = glm::vec2{ curr_mouse_pos.x - m_last_mouse_position.x, (curr_mouse_pos.y - m_last_mouse_position.y) * -1.f };
		auto const rotation = glm::vec3{ mouse_pos_offset * m_camera_sensitivity, 0.f };
		m_camera_perspective.get_component<agl::transformable>().rotate(rotation);
		m_last_mouse_position = agl::input::get_mouse_position();

		if(m_frame_count % 5 == 0)
			m_fps_text.get_component<agl::text>().text = std::to_string(frame_time * 1000.f) + "ms";

	}
}
