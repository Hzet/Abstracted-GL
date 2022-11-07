#pragma once
#include <vector>
#include "agl/core/misc/timer.hpp"
#include "agl/core/app/resource.hpp"
#include "agl/core/app/window.hpp"

namespace agl
{
	class application;

	extern std::unique_ptr<application> create_application();

	class application
	{
	public:
		static application& get_instance();		
		template <typename T>
		static T& get_resource();

	public:
		application();
		application(application&& other);
		application& operator=(application&& other) = default;

		void create(window&& wnd = window{});
		void shutdown();
		bool is_open() const;
		bool is_running() const;
		void run();

		window& get_window();

		virtual void init();

	protected:
		bool m_is_open;
		window m_window;

	protected:
		template <typename T>
		void add_resource();

	private:
		std::vector<std::unique_ptr<resource_base>> m_resources;
	};

#include "agl/core/app/application.inl"
}