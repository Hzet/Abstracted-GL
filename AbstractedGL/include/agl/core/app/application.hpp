#pragma once
#include <vector>
#include "core/misc/timer.hpp"
#include "core/app/resource.hpp"
#include "core/app/window.hpp"

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
		bool is_running() const;

		window& get_window();

		virtual void init() = 0;
		virtual void run() = 0;

	protected:
		window m_window;

	protected:
		template <typename T>
		void add_resource();

	private:
		std::vector<std::unique_ptr<resource_base>> m_resources;
	};

#include "core/app/application.inl"
}