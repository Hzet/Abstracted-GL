#include "core/app/application.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "utility/ecs/ecs.hpp"
#include "graphics/texture/texture-atlas.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-array.hpp"
#include "graphics/ecs/component/prism.hpp"
#include "graphics/ecs/component/uniform/transform.hpp"
#include "graphics/ecs/component/uniform/camera.hpp"
#include "graphics/ecs/component/uniform/spot-light.hpp"
#include "graphics/ecs/component/uniform/position.hpp"
#include "graphics/ecs/component/uniform/direction.hpp"
#include "graphics/ecs/component/uniform/material.hpp"
#include "core/misc/timer.hpp"
#include "core/app/input.hpp"

agl::entity create_camera(agl::registry &reg);
agl::entity create_cube(agl::registry &reg);
agl::entity create_spot_light(agl::registry &reg);

auto const cube_position = std::vector<agl::position>{
	{-0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{-0.5f,  0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},

	{-0.5f, -0.5f,  0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f,  0.5f},
	{-0.5f, -0.5f,  0.5f},

	{-0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f,  0.5f},
	{-0.5f,  0.5f,  0.5f},

	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},

	{-0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{-0.5f, -0.5f,  0.5f},
	{-0.5f, -0.5f, -0.5f},

	{-0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f, -0.5f}
};
auto const cube_color = std::vector<agl::color>(cube_position.size(), agl::color{0.f, 1.f, 0.f, 1.f});
auto const cube_normal = std::vector<agl::normal> {
	{ 0.0f,  0.0f, -1.0f },
	{ 0.0f,  0.0f, -1.0f },
	{ 0.0f,  0.0f, -1.0f },
	{ 0.0f,  0.0f, -1.0f },
	{ 0.0f,  0.0f, -1.0f },
	{ 0.0f,  0.0f, -1.0f },

	{ 0.0f,  0.0f, 1.0f, },
	{ 0.0f,  0.0f, 1.0f, },
	{ 0.0f,  0.0f, 1.0f, },
	{ 0.0f,  0.0f, 1.0f, },
	{ 0.0f,  0.0f, 1.0f, },
	{ 0.0f,  0.0f, 1.0f, },
	
	{ 1.0f,  0.0f,  0.0f },
	{ 1.0f,  0.0f,  0.0f },
	{ 1.0f,  0.0f,  0.0f },
	{ 1.0f,  0.0f,  0.0f },
	{ 1.0f,  0.0f,  0.0f },
	{ 1.0f,  0.0f,  0.0f },
	
	{ 1.0f,  0.0f,  0.0f },
	{ 1.0f,  0.0f,  0.0f },
	{ 1.0f,  0.0f,  0.0f },
	{ 1.0f,  0.0f,  0.0f },
	{ 1.0f,  0.0f,  0.0f },
	{ 1.0f,  0.0f,  0.0f },
	
	{ 0.0f, -1.0f,  0.0f },
	{ 0.0f, -1.0f,  0.0f },
	{ 0.0f, -1.0f,  0.0f },
	{ 0.0f, -1.0f,  0.0f },
	{ 0.0f, -1.0f,  0.0f },
	{ 0.0f, -1.0f,  0.0f },
	
	{ 0.0f,  1.0f,  0.0f },
	{ 0.0f,  1.0f,  0.0f },
	{ 0.0f,  1.0f,  0.0f },
	{ 0.0f,  1.0f,  0.0f },
	{ 0.0f,  1.0f,  0.0f },
	{ 0.0f,  1.0f,  0.0f },
};

auto const camera_velocity = 54.2f;
auto const mouse_sensitivity = 0.3f;

class test_app
	: public agl::application
{
public:
	void application::init()
	{
		add_resource<agl::texture_atlas>();
		add_resource<agl::shader_manager>();
		add_resource<agl::registry>();
	}
	void application::run()
	{
		// TODO: wypierdolic to stad 
		auto& sh_manager = get_resource<agl::shader_manager>();
		//sh_manager.load_from_file("resource/basic.vsh", "resource/basic.fsh");
		sh_manager.load_from_file("resource/light.vsh", "resource/light.fsh");

		auto& manager = application::get_resource<agl::shader_manager>();
		manager.link_all_shaders();

		auto& reg = get_resource<agl::registry>();

		// END TODO

		auto camera_entity = create_camera(reg);
		auto& camera = camera_entity.get_component<agl::camera_perspective>();
		auto& camera_transform = camera_entity.get_component<agl::transformable>();
		auto& camera_direction = camera_entity.get_component<agl::direction>();

		for (auto i = 0; i < 1000; ++i)
			create_cube(reg);

		auto spot_light_entity = create_spot_light(reg);
		
		auto last_mouse_pos = agl::input::get_mouse_position();

		auto timer = agl::timer{};
		auto frames = 0;

		auto frame_timer = agl::timer{};

		//auto prism_entity = reg.create();
		//auto& prism = prism_entity.attach_component<agl::prism>(sh_manager.get_shader_uid(0));
		//prism.set_radius(1.5f);
		//prism.set_side_count(15);
		//prism.set_sides(glm::vec2{ 0.2f, 10.2f });
		//prism.set_color(agl::color{ 1.f, 0.f, 1.f, 1.f });
		////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//
		//prism_entity.attach_component<agl::transformable>();
		//prism.get_uniforms().add_uniform<agl::transform_uniform, agl::transformable>(sh_manager.get_shader_uid(0));

		while (is_running())
		{
			auto frame_time = frame_timer.elapsed().seconds();
			frame_timer.reset();

			//if (timer.elapsed().seconds() >= 10.f)
			//	break;

			++frames;

			auto e = agl::event{};
			while (m_window.poll_event(e))
			{
				switch (e.type)
				{
				case agl::WINDOW_CLOSED:
					shutdown();
					return;
				}
			}

			if (agl::input::key_pressed(agl::ESCAPE))
			{
				shutdown();
				break;
			}
			if (agl::input::key_pressed(agl::A))
			{
				camera_transform.move(camera_direction.right * -camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::D))
			{
				camera_transform.move(camera_direction.right * camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::W))
			{
				camera_transform.move(camera_direction.forward * camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::S))
			{
				camera_transform.move(camera_direction.forward * -camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::LEFT_CONTROL))
			{
				camera_transform.move(camera_direction.up * -camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::SPACE))
			{
				camera_transform.move(camera_direction.up * camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::P))
			{
				camera.look_at({0,0,0});
			}
			if (agl::input::key_pressed(agl::E))
			{
				camera_transform.rotate(glm::vec3{ 0.f, 0.f, -5.f });
			}
			if (agl::input::key_pressed(agl::Q))
			{
				camera_transform.rotate(glm::vec3{ 0.f, 0.f, 5.f});
			}

			auto const curr_mouse_pos = agl::input::get_mouse_position();
			auto const mouse_pos_offset = glm::vec2{ curr_mouse_pos.x - last_mouse_pos.x, (curr_mouse_pos.y - last_mouse_pos.y) * -1.f };
			auto const rotation = glm::vec3{ mouse_pos_offset * mouse_sensitivity, 0.f };
			camera_transform.rotate(rotation);
			last_mouse_pos = agl::input::get_mouse_position();

			m_window.clear();
			reg.update();
			m_window.display();
		}

		AGL_LOG_INFO("\nAverage FPS: {}\nAverage frame time: {}ms\nFrames: {}\nDuration: {}s", frames / timer.elapsed().seconds(), timer.elapsed().milliseconds() / frames, frames, timer.elapsed().seconds());
	}
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

		auto app = std::make_unique<test_app>();
		app->create(std::move(wnd));

		return app;
	}
}

int main(int argc, char **argv)
{
	try
	{
		auto& app = agl::application::get_instance();

		app.run();

		app.shutdown();
	}
	catch (std::exception& e)
	{
		AGL_CORE_LOG_ERROR("Exception raised: {}", e.what());
	}
}

agl::entity create_camera(agl::registry &reg)
{
	static auto const& sh_manager = agl::application::get_resource<agl::shader_manager>();

	agl::entity result = reg.create();

	auto& camera = result.attach_component<agl::camera_perspective>();
	auto& camera_transform = result.attach_component<agl::transformable>();
	auto& camera_direction = result.attach_component<agl::direction>(agl::camera_base::s_world_direction);
	auto& uniforms = result.attach_component<agl::uniform_array>();

	camera.set_frame_dimensions(agl::application::get_instance().get_window().get_data().resolution);
	camera.set_planes({ 0.1f, 100000.f });
	camera.set_fov(60.f);
	camera.look_at({ 0.f, 0.f, 0.f });
	
	camera_transform.set_position({ 0.f, 5.f, 0.f });

	uniforms.add_uniform<agl::camera_uniform, agl::camera_perspective>({ sh_manager.get_shader_uid(0) });
	uniforms.add_uniform<agl::position_uniform, agl::transformable>({ sh_manager.get_shader_uid(0) });

	auto& position_uniform = uniforms.get_uniform<agl::position_uniform>();
	position_uniform.set_name("camera");

	return result;
}

agl::entity create_cube(agl::registry &reg)
{
	static auto const& sh_manager = agl::application::get_resource<agl::shader_manager>();

	agl::entity result = reg.create();

	auto& mesh = result.attach_component<agl::mesh>();
	auto& transform = result.attach_component<agl::transformable>();
	auto& material = result.attach_component<agl::material>();

	mesh.draw_type = agl::DRAW_TRIANGLES;
	mesh.id_shader = sh_manager.get_shader_uid(0);
	mesh.rbuffer.set_vertex_count(cube_position.size());
	mesh.rbuffer.add_vertices<agl::position>(cube_position.data());
	mesh.rbuffer.add_vertices<agl::color>(cube_color.data());
	mesh.rbuffer.add_vertices<agl::normal>(cube_normal.data());

	transform.set_position({ glm::sphericalRand(50.f) });

	auto& uniforms = result.attach_component<agl::uniform_array>();
	uniforms.add_uniform<agl::transform_uniform, agl::transformable>(sh_manager.get_shader_uid(0));
	uniforms.add_uniform<agl::material_uniform, agl::material>(sh_manager.get_shader_uid(0));

	material.ambient = glm::vec4{ 1.0f, 0.5f, 0.31f, 1.f };
	material.diffuse = glm::vec4{ 1.0f, 0.5f, 0.31f, 1.f };
	material.specular = glm::vec4{ 0.5f, 0.5f, 0.5f, 1.f };
	material.shininess = 32.f;

	return result;
}

agl::entity create_spot_light(agl::registry &reg)
{
	static auto const& sh_manager = agl::application::get_resource<agl::shader_manager>();

	agl::entity result = reg.create();

	auto& light = result.attach_component<agl::spot_light>();
	auto& dir = result.attach_component<agl::direction>();
	auto& transform = result.attach_component<agl::transformable>();
	auto& uniforms = result.attach_component<agl::uniform_array>();

	light.ambient = glm::vec4{ 0.2f, 0.2f, 0.2f, 1.f };
	light.diffuse = glm::vec4{ 0.5f, 0.5f, 0.5f, 1.f };
	light.specular = glm::vec4{ 1.f, 1.f, 1.f, 1.f };
	light.color = glm::vec4{ 0.f };

	uniforms.add_uniform<agl::position_uniform, agl::transformable>({ sh_manager.get_shader_uid(0) });
	uniforms.add_uniform<agl::spot_light_uniform, agl::spot_light>({ sh_manager.get_shader_uid(0) });
	uniforms.add_uniform<agl::direction_uniform, agl::direction>({ sh_manager.get_shader_uid(0) });

	//auto& direction_uniform = uniforms.get_uniform<agl::direction_uniform>();
	//auto& spot_light_uniform = uniforms.get_uniform<agl::spot_light_uniform>();
	//auto& position_uniform = uniforms.get_uniform<agl::position_uniform>();
	//
	//position_uniform.set_name(spot_light_uniform.get_name());
	//direction_uniform.set_name(spot_light_uniform.get_name());

	return result;
}