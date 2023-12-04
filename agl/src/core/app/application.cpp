#include "agl/core/app/application.hpp"
#include "agl/core/app/layer-manager.hpp"
#include "agl/graphics/text/font-manager.hpp"
#include "agl/graphics/texture/texture-manager.hpp"
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/ecs/ecs.hpp"
#include "agl/logger/log.hpp"

namespace agl
{

	application& application::get_instance()
	{
		static auto instance = create_application();

		return *instance;
	}

	application::application()
		: m_is_open{ false }
	{

	}

	application::application(application&& other)
		: m_resources{ std::move(m_resources) }
		, m_window{ std::move(other.m_window) }
	{
	}

	void application::create(window&& wnd)
	{
		m_is_open = true;
		m_window = std::move(wnd);
	}

	void application::shutdown()
	{
		m_is_open = false;
		m_window.close();
		m_resources.clear();
	}

	bool application::is_open() const
	{
		return m_is_open;
	}

	bool application::is_running() const
	{
		return m_window.is_open();
	}

	void application::run()
	{
		auto& reg = get_resource<agl::registry>();
		auto& layers = get_resource<agl::layer_manager>();

		auto frames = 0;
		auto frame_timer = agl::timer{};
		auto timer = agl::timer{};

		while (is_running())
		{
			auto frame_time = frame_timer.elapsed().seconds();
			frame_timer.reset();

			++frames;

			for (auto i = 0; i < layers.get_count(); ++i)
				layers[i].on_update();

			if (m_window.is_closed())
				break;

			m_window.clear();
			reg.update();
			m_window.display();
		}

		AGL_LOG_INFO("\nAverage FPS: {}\nAverage frame time: {}ms\nFrames: {}\nDuration: {}s", frames / timer.elapsed().seconds(), timer.elapsed().milliseconds() / frames, frames, timer.elapsed().seconds());
	}
	
	agl::window& application::get_window()
	{
		return m_window;
	}

	void application::init()
	{
		add_resource<agl::texture_manager>();
		add_resource<agl::shader_manager>();
		add_resource<agl::registry>();
		add_resource<agl::layer_manager>();
		add_resource<agl::font_manager>();
	}
}
