#include "agl/core/app/input.hpp"
#include "agl/core/app/layer-manager.hpp"

#include "editor.hpp"
#include "scene-layer.hpp"

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

		auto app = std::make_unique<editor::editor_application>();
		app->create(std::move(wnd));

		return app;
	}
}

namespace editor
{
	void editor_application::init()
	{
		agl::application::init();

		auto& layers = get_resource<agl::layer_manager>();
		layers.add_layer<editor::scene_layer>();
	}
}
