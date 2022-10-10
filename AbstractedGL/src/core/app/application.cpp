#include "core/app/application.hpp"

namespace agl
{

	application& application::get_instance()
	{
		static auto instance = create_application();

		return *instance;
	}

	application::application()
	{

	}

	application::application(application&& other)
		: m_resources{ std::move(m_resources) }
		, m_window{ std::move(other.m_window) }
	{
	}

	void application::create(window&& wnd)
	{
		init();

		m_window = std::move(wnd);
	}

	void application::shutdown()
	{
		m_window.close();
		m_resources.clear();
	}

	bool application::is_running() const
	{
		return m_window.is_open();
	}

	agl::window& application::get_window()
	{
		return m_window;
	}

}
