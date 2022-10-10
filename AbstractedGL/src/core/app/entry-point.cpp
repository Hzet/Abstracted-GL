#include "core/app/application.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "utility/ecs/ecs.hpp"
#include "graphics/texture/texture-atlas.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/ecs/component/mesh.hpp"
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
auto const camera_velocity = 1.f;
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

		for (auto i = 0; i < 10000; ++i)
			create_cube(reg);

		auto cube_entity = create_cube(reg);
		auto& cube = cube_entity.get_component<agl::mesh>();

		auto last_mouse_pos = agl::input::get_mouse_position();

		auto timer = agl::timer{};
		auto frames = 0;

		while (is_running())
		{
			if (timer.elapsed().seconds() >= 10.f)
				break;

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
				return;
			}
			if (agl::input::key_pressed(agl::A))
			{
				camera.move(camera.get_direction().right * -camera_velocity);
			}
			if (agl::input::key_pressed(agl::D))
			{
				camera.move(camera.get_direction().right * camera_velocity);
			}
			if (agl::input::key_pressed(agl::W))
			{
				camera.move(camera.get_direction().forward * camera_velocity);
			}
			if (agl::input::key_pressed(agl::S))
			{
				camera.move(camera.get_direction().forward * -camera_velocity);
			}
			if (agl::input::key_pressed(agl::LEFT_CONTROL))
			{
				camera.move(camera.get_direction().up * -camera_velocity);
			}
			if (agl::input::key_pressed(agl::SPACE))
			{
				camera.move(camera.get_direction().up * camera_velocity);
			}
			if (agl::input::key_pressed(agl::P))
			{
				camera.look_at(cube_entity.get_component<agl::transformable>().get_position());
			}

			auto mouse_pos_offset = glm::vec2{ agl::input::get_mouse_position().x - last_mouse_pos.x, (agl::input::get_mouse_position().y - last_mouse_pos.y) * -1.f };
			camera.rotate(glm::vec3{ mouse_pos_offset * mouse_sensitivity, 0.f });
			last_mouse_pos = agl::input::get_mouse_position();

			m_window.clear();
			reg.update();
			m_window.display();
		}

		AGL_LOG_INFO("\nAverage FPS: {}\nFrames: {}", frames / timer.elapsed().seconds(), frames);
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

		wnd.create("Test app", { 800, 600 });
		wnd.set_clear_color({ 0.f, 1.f, 1.f, 1.f });
		wnd.set_clear_buffers(static_cast<gl_clear_type>(CLEAR_COLOR | CLEAR_DEPTH));
		wnd.set_clear_color({ 0.05f, 0.1f, 0.2f, 1.f });
		wnd.set_cursor_type(CURSOR_DISABLED);

		window::enable_feature(agl::FEATURE_DEPTH_TEST);

		auto app = std::make_unique<test_app>();
		app->create(std::move(wnd));

		return app;
	}
}

int main(int argc, char **argv)
{
	auto& app = agl::application::get_instance();

	app.run();

	app.shutdown();
}

agl::entity create_camera(agl::registry &reg)
{
	static auto const& sh_manager = agl::application::get_resource<agl::shader_manager>();

	agl::entity result = reg.create();

	auto &camera = result.attach_component<agl::camera_perspective>();
	auto &uniforms = result.attach_component<agl::uniform_array>();

	camera.set_frame_dimensions(agl::application::get_instance().get_window().get_data().resolution);
	camera.set_position({ 100.f, 0.f, 0.f });
	camera.set_planes({ 0.1f, 100000.f });
	camera.set_fov(60.f);
	camera.look_at({ 0.f, 0.f, 0.f });

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