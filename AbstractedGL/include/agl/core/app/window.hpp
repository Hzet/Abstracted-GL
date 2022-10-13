#pragma once
#include <unordered_map>

#include "system/glcore/gl-core.hpp"
#include "core/enums/input-mode.hpp"
#include "core/enums/gl-clear-type.hpp"
#include "core/enums/gl-feature-type.hpp"
#include "core/enums/gl-profile-type.hpp"
#include "core/app/window-data.hpp"
#include "system/glcore/destructive-move.hpp"

#include <GLFW/glfw3.h>

namespace agl
{
	class window
		: public destructive_move
	{
	public:
		static void init();
		static void enable_feature(gl_feature_type type);
		static void disable_feature(gl_feature_type type);
		static void set_opengl_api_version(std::uint32_t major, std::uint32_t minor);
		static void set_opengl_api_profile(gl_profile_type type);

	public:
		window();
		window(window &&other);
		window(const window&) = delete;
		window& operator=(window &&other);
		window& operator=(const window&) = delete;
		~window();

		void clear() const;
		void close();
		void create(const std::string &title, const glm::ivec2 &resolution);
		void display() const;
		bool is_open() const;
		bool is_closed() const;
		bool poll_event(event &event);

		window_data const& get_data() const;

		const glm::vec4& get_clear_color() const;
		void set_clear_color(const glm::vec4 &color);

		gl_clear_type get_clear_buffers() const;
		void set_clear_buffers(gl_clear_type type);

		cursor_type get_cursor_type() const;
		void set_cursor_type(cursor_type);

		bool get_input_mode(input_mode mode);
		void set_input_mode(input_mode mode, bool status);

		bool get_vsync() const;
		void set_vsync(bool status);

	private:
		struct glfw_window_deleter
		{
			void operator()(GLFWwindow *window) {}
		};

	private:
		friend class window_system;
		friend class input;

	private:
		GLFWwindow* get_handle();
		void shutdown();

	private:
		static std::int64_t s_window_count;

		glm::vec4 m_clear_color;
		gl_clear_type m_clear_type;
		window_data m_data;
		std::unique_ptr<GLFWwindow, glfw_window_deleter> m_handle;
		bool m_poll_events;
	};
}