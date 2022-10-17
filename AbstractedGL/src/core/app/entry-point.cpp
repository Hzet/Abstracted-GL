#include "core/app/application.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "utility/ecs/ecs.hpp"
#include "graphics/texture/texture-atlas.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/ecs/component/prism.hpp"
#include "graphics/ecs/component/transformable.hpp"
#include "graphics/ecs/component/uniform/transform-uniform.hpp"
#include "graphics/ecs/component/uniform/camera-uniform.hpp"
#include "core/misc/timer.hpp"
#include "core/app/input.hpp"

agl::entity create_camera(agl::registry &reg);
agl::entity create_cube(agl::registry &reg);

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
auto const cube_color = std::vector<agl::color> {
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f},
	{1.f, 1.f, 1.f, 1.f}
};
auto const camera_velocity = 4.2f;
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
		sh_manager.load_from_file("resource/basic.vsh", "resource/basic.fsh");
		//sh_manager.load_from_file("resource/light.vsh", "resource/light.fsh");

		auto& manager = application::get_resource<agl::shader_manager>();
		manager.link_all_shaders();

		auto& reg = get_resource<agl::registry>();

		// END TODO

		auto camera_entity = create_camera(reg);
		auto& camera = camera_entity.get_component<agl::camera_perspective>();
		auto& camera_transform = camera_entity.get_component<agl::transformable>();

		for (auto i = 0; i < 1000; ++i)
			create_cube(reg);
		
		auto last_mouse_pos = agl::input::get_mouse_position();

		auto timer = agl::timer{};
		auto frames = 0;

		auto frame_timer = agl::timer{};

		//auto prism_entity = reg.create();
		//auto& prism = prism_entity.attach_component<agl::prism>(sh_manager.get_shader_uid(0));
		//prism.set_radius(1.5f);
		//prism.set_side_count(15);
		//prism.set_sides(glm::vec2{ 0.2f, 10.2f });
		//prism.set_color(agl::color::White);
		////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//
		//prism_entity.attach_component<agl::transformable>();
		//prism.get_uniforms().add_uniform<agl::transform_uniform>(sh_manager.get_shader_uid(0));

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
				camera_transform.move(camera.get_direction().right * -camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::D))
			{
				camera_transform.move(camera.get_direction().right * camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::W))
			{
				camera_transform.move(camera.get_direction().forward * camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::S))
			{
				camera_transform.move(camera.get_direction().forward * -camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::LEFT_CONTROL))
			{
				camera_transform.move(camera.get_direction().up * -camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::SPACE))
			{
				camera_transform.move(camera.get_direction().up * camera_velocity * frame_time);
			}
			if (agl::input::key_pressed(agl::P))
			{
				camera.look_at({0,0,0});
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
	auto& uniforms = result.attach_component<agl::uniform_array>();

	camera.set_frame_dimensions(agl::application::get_instance().get_window().get_data().resolution);
	camera.set_planes({ 0.1f, 100000.f });
	camera.set_fov(60.f);
	camera.look_at({ 0.f, 0.f, 0.f });
	
	camera_transform.set_position({ 0.f, 5.f, 0.f });

	uniforms.add_uniform<agl::camera_uniform>({ sh_manager.get_shader_uid(0) });

	return result;
}

agl::entity create_cube(agl::registry &reg)
{
	static auto const& sh_manager = agl::application::get_resource<agl::shader_manager>();

	agl::entity result = reg.create();

	auto &mesh = result.attach_component<agl::mesh>();
	auto &transform = result.attach_component<agl::transformable>();

	mesh.draw_type = agl::DRAW_TRIANGLES;
	mesh.id_shader = sh_manager.get_shader_uid(0);
	mesh.rbuffer.set_vertex_count(cube_position.size());
	mesh.rbuffer.add_vertices<agl::position>(cube_position.data());
	mesh.rbuffer.add_vertices<agl::color>(cube_color.data());
	mesh.uniforms.add_uniform<agl::transform_uniform>(sh_manager.get_shader_uid(0));

	transform.set_position({ glm::sphericalRand(50.f) });

	return result;
}