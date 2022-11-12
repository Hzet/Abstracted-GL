#include "agl/core/app/application.hpp"
#include "agl/core/app/input.hpp"
#include "agl/core/app/layer-base.hpp"
#include "agl/core/app/layer-manager.hpp"
#include "agl/graphics/shader/uniform-array.hpp"
#include "agl/graphics/ecs/component/uniform/camera.hpp"
#include "agl/graphics/ecs/component/uniform/position.hpp"
#include "agl/graphics/ecs/component/uniform/transform.hpp"
#include "agl/graphics/ecs/component/uniform/material.hpp"
#include "agl/graphics/ecs/component/renderable.hpp"
#include "agl/graphics/ecs/component/mesh.hpp"
#include "agl/graphics/shape/rectangle.hpp"
#include "agl/graphics/shape/prism.hpp"

class scene_layer
	: public agl::layer_base
{
public:
	virtual void on_attach() override
	{
		auto& reg = agl::application::get_resource<agl::registry>();
		auto& sh_manager = agl::application::get_resource<agl::shader_manager>();

		// load shaders
		auto const basic_shader = sh_manager.load_from_file("resource/basic.vsh", "resource/basic.fsh");
		auto const light_shader = sh_manager.load_from_file("resource/light.vsh", "resource/light.fsh");
		sh_manager.link_all_shaders();

		// camera
		m_camera_velocity = 40.f;
		m_camera_sensitivity = 0.3f;

		m_camera = reg.create();

		auto& camera = m_camera.attach_component<agl::camera_perspective>();
		auto& camera_transform = m_camera.attach_component<agl::transformable>();
		auto& camera_direction = m_camera.attach_component<agl::direction>(agl::camera_base::s_world_direction);
		auto& uniforms = m_camera.attach_component<agl::uniform_array>();

		camera.set_frame_dimensions(agl::application::get_instance().get_window().get_data().resolution);
		camera.set_planes({ 0.1f, 100000.f });
		camera.set_fov(60.f);
		camera.look_at({ 0.f, 0.f, 0.f });

		camera_transform.set_position({ 0.f, 5.f, 0.f });

		uniforms.add_uniform<agl::camera_uniform, agl::camera_perspective>(basic_shader);

		// mesh 
		auto prism_entity = reg.create();
		auto prism_builder = agl::prism_builder{4, glm::sqrt(2.f) / 2.f, 1.f};

		prism_builder.set_color(agl::color{ 0.f, 1.f, 0.f, 1.f });

		auto const prism_positions = prism_builder.get_positions();
		auto const prism_colors = prism_builder.get_colors();
		auto const prism_indices = prism_builder.get_indices();
		
		auto& prism_mesh = prism_entity.attach_component<agl::mesh>();
		prism_mesh.draw_type = prism_builder.get_draw_type();
		prism_mesh.rbuffer.add_indices(prism_indices);
		prism_mesh.rbuffer.set_vertex_count(prism_builder.get_vertex_count());
		prism_mesh.rbuffer.set_vertices(prism_positions);
		prism_mesh.rbuffer.set_vertices(prism_colors);

		for (auto i = 0; i < 1000; ++i)
		{
			auto renderable = agl::renderable{ prism_entity.get_entity_uid(), basic_shader };

			auto e = reg.create();
			auto& transform = e.attach_component<agl::transformable>();
			auto& material = e.attach_component<agl::material>();
			e.attach_component<agl::renderable>(renderable);

			auto& uniforms = e.attach_component<agl::uniform_array>();
			uniforms.add_uniform<agl::transform_uniform, agl::transformable>(basic_shader);
			//uniforms.add_uniform<agl::material_uniform, agl::material>(basic_shader);

			material.ambient = glm::vec4{ 0.f };
			material.diffuse = glm::vec4{ 1.0f, 1.0f, 0.31f, 1.f };
			material.specular = glm::vec4{ 1.f };
			material.shininess = 32.f;

			transform.set_position({ glm::sphericalRand(50.f) });
		}

		// rectangle 
		auto rect_builder = agl::rectangle_builder{ agl::rectangle{{10.f, 20.f}} };
		rect_builder.set_color(agl::color{ 1.f, 0.f, 0.f, 1.f });

		auto rect_entity = reg.create();
		rect_entity.attach_component<agl::renderable>(rect_entity, basic_shader);
		auto& rect_mesh = rect_entity.attach_component<agl::mesh>();
		auto& rect_transform = rect_entity.attach_component<agl::transformable>();
		auto& rect_uniforms = rect_entity.attach_component<agl::uniform_array>();

		auto const rect_indices = rect_builder.get_indices();
		auto const rect_positions = rect_builder.get_positions();
		auto const rect_colors = rect_builder.get_colors();
		rect_mesh.draw_type = rect_builder.get_draw_type();
		rect_mesh.rbuffer.add_indices(rect_indices);
		rect_mesh.rbuffer.set_vertex_count(rect_builder.get_vertex_count());
		rect_mesh.rbuffer.set_vertices(rect_positions);
		rect_mesh.rbuffer.set_vertices(rect_colors);

		rect_uniforms.add_uniform<agl::transform_uniform, agl::transformable>(basic_shader);
	}

	virtual void on_update() override
	{
		auto frame_time = m_timer.elapsed().seconds();
		m_timer.reset();

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
			m_camera.get_component<agl::transformable>().move(m_camera.get_component<agl::direction>().right * -m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::D))
		{
			m_camera.get_component<agl::transformable>().move(m_camera.get_component<agl::direction>().right * m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::W))
		{
			m_camera.get_component<agl::transformable>().move(m_camera.get_component<agl::direction>().forward * m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::S))
		{
			m_camera.get_component<agl::transformable>().move(m_camera.get_component<agl::direction>().forward * -m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::LEFT_CONTROL))
		{
			m_camera.get_component<agl::transformable>().move(m_camera.get_component<agl::direction>().up * -m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::SPACE))
		{
			m_camera.get_component<agl::transformable>().move(m_camera.get_component<agl::direction>().up * m_camera_velocity * frame_time);
		}
		if (agl::input::key_pressed(agl::P))
		{
			m_camera.get_component<agl::camera_perspective>().look_at({ 0,0,0 });
		}
		if (agl::input::key_pressed(agl::E))
		{
			m_camera.get_component<agl::transformable>().rotate(glm::vec3{ 0.f, 0.f, -5.f });
		}
		if (agl::input::key_pressed(agl::Q))
		{
			m_camera.get_component<agl::transformable>().rotate(glm::vec3{ 0.f, 0.f, 5.f });
		}

		auto const curr_mouse_pos = agl::input::get_mouse_position();
		auto const mouse_pos_offset = glm::vec2{ curr_mouse_pos.x - m_last_mouse_position.x, (curr_mouse_pos.y - m_last_mouse_position.y) * -1.f };
		auto const rotation = glm::vec3{ mouse_pos_offset * m_camera_sensitivity, 0.f };
		m_camera.get_component<agl::transformable>().rotate(rotation);
		m_last_mouse_position = agl::input::get_mouse_position();
	}

private:
	agl::entity m_camera;
	float m_camera_velocity;
	float m_camera_sensitivity;
	agl::timer m_timer;
	glm::vec2 m_last_mouse_position;
};

class editor
	: public agl::application
{
public:
	virtual void init() override
	{
		agl::application::init();

		auto& layers = get_resource<agl::layer_manager>();
		layers.add_layer<scene_layer>();
	}
private:
};

namespace agl
{
	std::unique_ptr<agl::application> create_application()
	{
		window::init();
		window::set_opengl_api_version(4, 3);
		window::set_opengl_api_profile(OPENGL_CORE_PROFILE);

		auto wnd = window{};

		wnd.create("Test app", { 1920, 1080 });
		wnd.set_clear_color({ 0.f, 1.f, 1.f, 1.f });
		wnd.set_clear_buffers(static_cast<gl_clear_type>(CLEAR_COLOR | CLEAR_DEPTH));
		wnd.set_clear_color({ 0.05f, 0.1f, 0.2f, 1.f });
		wnd.set_cursor_type(CURSOR_DISABLED);
		wnd.set_vsync(false);

		window::enable_feature(agl::FEATURE_DEPTH_TEST);

		auto app = std::make_unique<editor>();
		app->create(std::move(wnd));

		return app;
	}
}
