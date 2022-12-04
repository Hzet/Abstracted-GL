#include "agl/core/app/application.hpp"
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/system/debug/error.hpp"

namespace agl
{
	static void glfw_error_callback(int error, const char *description);
	static void glfw_set_callbacks(GLFWwindow *handle);
	//static void glfw_window_button_input_callback(GLFWwindow *window, int button, int action, int mods);
	static void glfw_window_char_callback(GLFWwindow *window, unsigned int codepoint);
	static void glfw_window_close_callback(GLFWwindow *window);
	static void glfw_window_cursor_enter_callback(GLFWwindow *window, int entered);
	//static void glfw_window_cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
	static void glfw_window_focus_callback(GLFWwindow *window, int focused);
	static void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height);
	static void glfw_window_iconify_callback(GLFWwindow *window, int iconified);
	//static void glfw_window_key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void glfw_window_maximize_callback(GLFWwindow *window, int maximnized);
	static void glfw_window_scale_callback(GLFWwindow *window, float xscale, float yscale);
	static void glfw_window_scroll_input_callback(GLFWwindow *window, double xoffset, double yoffset);
	static void glfw_window_size_callback(GLFWwindow *window, int width, int height);

#ifdef AGL_DEBUG
	static void glfw_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
#endif
	
	std::int64_t window::s_window_count = 0;

	void window::create(const std::string &title, const glm::ivec2 &resolution)
	{
		// create a window instance
		m_data.title = title;
		m_data.resolution = resolution;
		m_handle = std::unique_ptr<GLFWwindow, glfw_window_deleter>(glfwCreateWindow(resolution.x, resolution.y, title.c_str(), nullptr, nullptr));

		if (m_handle == nullptr)
			AGL_CORE_EXCEPTION(ExGLFWNoWindowContext, "Failed to create a window!");

		glfwMakeContextCurrent(m_handle.get());

		// initialize GLAD library
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			AGL_CORE_EXCEPTION(ExGLAD, "Failed to initialize OpenGL context!");

#ifdef AGL_DEBUG
		enable_feature(FEATURE_DEBUG_OUTPUT);
		enable_feature(FEATURE_DEBUG_OUTPUT_SYNCHRONOUS);
		
		AGL_CALL(glDebugMessageCallback(glfw_debug_callback, 0));
		AGL_CALL(glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE));

#endif

		glfwSetWindowUserPointer(m_handle.get(), reinterpret_cast<void*>(&m_data));

		glfw_set_callbacks(m_handle.get());
	}

	void window::display() const
	{
		glfwSwapBuffers(m_handle.get());
	}

	void window::init()
	{
		if (s_window_count == 0)
		{
			if (!glfwInit())
				AGL_CORE_EXCEPTION(ExGLFWNotInitialized, "Failed to initialize GLFW!");

			glfwSetErrorCallback(glfw_error_callback);
		}
	}

	void window::enable_feature(gl_feature_type type)
	{
		AGL_CALL(glEnable(type));
	}

	void window::disable_feature(gl_feature_type type)
	{
		AGL_CALL(glDisable(type));
	}

	void window::set_opengl_api_version(std::uint32_t major, std::uint32_t minor)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	}

	window::window()
		: m_handle(nullptr)
		, m_poll_events(true)
	{
	}

	window::window(window &&other)
		: destructive_move(std::move(other))
		, m_clear_color(other.m_clear_color)
		, m_clear_type(other.m_clear_type)
		, m_data(std::move(other.m_data))
		, m_handle(std::move(other.m_handle))
		, m_poll_events(true)
	{
		glfwSetWindowUserPointer(m_handle.get(), &m_data);
	}

	window& window::operator=(window &&other)
	{
		destructive_move::operator=(std::move(other));
		
		m_clear_color = std::move(other.m_clear_color);
		m_clear_type = other.m_clear_type;
		m_data = std::move(other.m_data);
		m_handle = std::move(other.m_handle);
		m_poll_events = true;

		glfwSetWindowUserPointer(m_handle.get(), &m_data);

		return *this;
	}

	window::~window()
	{
		if (!is_move_constructing())
			shutdown();
	}


	void window::clear() const
	{
		AGL_CALL(glClearColor(m_clear_color.x, m_clear_color.y, m_clear_color.z, m_clear_color.w));
		AGL_CALL(glClear(m_clear_type));
	}

	window_data const& window::get_data() const
	{
		return m_data;
	}

	const glm::vec4& window::get_clear_color() const
	{
		return m_clear_color;
	}

	void window::set_clear_color(const glm::vec4 &color)
	{
		m_clear_color = color;
	}

	gl_clear_type window::get_clear_buffers() const
	{
		return m_clear_type;
	}

	void window::set_clear_buffers(gl_clear_type type)
	{
		m_clear_type = type;
	}

	cursor_type window::get_cursor_type() const
	{
		return static_cast<cursor_type>(glfwGetInputMode(m_handle.get(), GLFW_CURSOR));
	}

	void window::set_cursor_type(cursor_type type)
	{
		glfwSetInputMode(m_handle.get(), GLFW_CURSOR, type);
	}

	GLFWwindow* window::get_handle()
	{
		return m_handle.get();
	}

	void window::shutdown()
	{
		if (s_window_count == 0)
			return;

		s_window_count--;

		glfwDestroyWindow(m_handle.get());
		if (s_window_count == 0)
			glfwTerminate();

		m_handle = nullptr;
	}
	
	bool window::is_open() const
	{
		return !m_data.closed && !m_data.minimized;
	}

	bool window::is_closed() const
	{
		return m_data.closed;
	}

	void window::close()
	{
		m_data.closed = true;
		glfwSetWindowShouldClose(m_handle.get(), GLFW_TRUE);
	}

	bool window::poll_event(event &e)
	{
		if (m_poll_events)
		{
			glfwPollEvents();
			m_poll_events = false;
		}

		if (m_data.events.empty())
		{
			m_poll_events = true;
			return false;
		}

		e = m_data.events.front();
		m_data.events.pop();
		return true;
	}

	void window::set_input_mode(input_mode mode, bool status)
	{
		glfwSetInputMode(m_handle.get(), mode, (status ? GLFW_TRUE : GLFW_FALSE));
	}

	bool window::get_vsync() const
	{
		return m_data.vsync;
	}

	void window::set_vsync(bool status)
	{
		m_data.vsync = status;
		glfwSwapInterval(status ? 1 : 0);
	}

	bool window::get_input_mode(input_mode mode)
	{
		return glfwGetInputMode(m_handle.get(), mode);
	}

	void window::set_opengl_api_profile(gl_profile_type type)
	{
		glfwWindowHint(GLFW_OPENGL_PROFILE, type);
	}

	void window::set_blend_function(gl_blend_function sfactor, gl_blend_function dfactor)
	{
		AGL_CALL(glBlendFunc(sfactor, dfactor));
	}

	void glfw_error_callback(int error, const char *description)
	{
		switch (error)
		{
		case GLFW_NOT_INITIALIZED: AGL_CORE_EXCEPTION(ExGLFWNotInitialized, "Message: {}", description);
		case GLFW_NO_CURRENT_CONTEXT: AGL_CORE_EXCEPTION(ExGLFWNoCurrentContext, "Message: {}", description);
		case GLFW_INVALID_ENUM: AGL_CORE_EXCEPTION(ExGLFWInvalidEnum, "Message: {}", description);
		case GLFW_INVALID_VALUE: AGL_CORE_EXCEPTION(ExGLFWInvalidValue, "Message: {}", description);
		case GLFW_OUT_OF_MEMORY: AGL_CORE_EXCEPTION(ExGLFWOutOfMemory, "Message: {}", description);
		case GLFW_API_UNAVAILABLE: AGL_CORE_EXCEPTION(ExGLFWUnavailable, "Message: {}", description);
		case GLFW_PLATFORM_ERROR: AGL_CORE_EXCEPTION(ExGLFWPlatform, "Message: {}", description);
		case GLFW_FORMAT_UNAVAILABLE: AGL_CORE_EXCEPTION(ExGLFWFormatUnavailable, "Message: {}", description);
		case GLFW_NO_WINDOW_CONTEXT: AGL_CORE_EXCEPTION(ExGLFWNoWindowContext, "Message: {}", description);
		}
	}

	void glfw_set_callbacks(GLFWwindow *handle)
	{
		glfwSetWindowSizeCallback(handle, glfw_window_size_callback);
		glfwSetWindowCloseCallback(handle, glfw_window_close_callback);
		glfwSetWindowFocusCallback(handle, glfw_window_focus_callback);
		glfwSetWindowMaximizeCallback(handle, glfw_window_maximize_callback);
		glfwSetWindowIconifyCallback(handle, glfw_window_iconify_callback);
		glfwSetWindowContentScaleCallback(handle, glfw_window_scale_callback);
		//glfwSetKeyCallback(handle, glfw_window_key_input_callback);
		glfwSetCharCallback(handle, glfw_window_char_callback);
		//glfwSetCursorPosCallback(handle, glfw_window_cursor_position_callback);
		glfwSetCursorEnterCallback(handle, glfw_window_cursor_enter_callback);
		//glfwSetMouseButtonCallback(handle, glfw_window_button_input_callback);
		glfwSetScrollCallback(handle, glfw_window_scroll_input_callback);
		glfwSetFramebufferSizeCallback(handle, glfw_framebuffer_size_callback);
	}

/*
	void glfw_window_button_input_callback(GLFWwindow *window, int button, int action, int mods)
	{
		auto &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		auto e = event{};
		switch (action)
		{
		case GLFW_PRESS:
			e.type = MOUSE_KEY_PRESSED;
			break;
		case GLFW_RELEASE:
			e.type = MOUSE_KEY_RELEASED;
			break;
		}

		e.button.code = static_cast<button_type>(button);
		e.button.bit_modifiers = mods;

		data.events.push(e);
	}*/

	void glfw_window_char_callback(GLFWwindow *window, unsigned int codepoint)
	{
		auto &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		auto e = event{};
		e.type = TEXT_ENTERED;
		e.character = codepoint;

		data.events.push(e);
	}

	void glfw_window_close_callback(GLFWwindow *window)
	{
		auto& data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		data.closed = true;

		auto e = event{};
		e.type = WINDOW_CLOSED;

		data.events.push(e);
	}

	void glfw_window_cursor_enter_callback(GLFWwindow *window, int entered)
	{
		auto&data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		auto e = event{};
		e.type = entered ? MOUSE_ENTERED : MOUSE_LEFT;

		data.events.push(e);
	}

/*
	void glfw_window_cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
	{
		auto&data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		auto e = event{};
		e.type = MOUSE_MOVED;
		e.position = { static_cast<float>(xpos), static_cast<float>(ypos) };

		data.events.push(e);
	}*/

	void glfw_window_focus_callback(GLFWwindow *window, int focused)
	{
		auto&data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		data.focused = true;

		auto e = event{};
		e.type = focused ? WINDOW_GAINED_FOCUS : WINDOW_LOST_FOCUS;

		data.events.push(e);
	}

	void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height)
	{
		auto& data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		data.framebufferSize.x = width;
		data.framebufferSize.y = height;

		AGL_CALL(glViewport(0, 0, width, height));
	}

	void glfw_window_iconify_callback(GLFWwindow *window, int iconified)
	{
		auto& data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		if (iconified)
			data.minimized = true;
		else
			data.minimized = false;

		auto e = event{};
		e.type = iconified ? WINDOW_MINIMIZED : WINDOW_RESTORED;

		data.events.push(e);
	}

	/*void glfw_window_key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		auto& data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		auto e = event{};
		switch (action)
		{
		case GLFW_PRESS:
			e.type = KEY_PRESSED;
			break;
		case GLFW_RELEASE:
			e.type = KEY_RELEASED;
			break;
		case GLFW_REPEAT:
			e.type = KEY_REPEATED;
			break;
		}

		e.key.code = static_cast<Keyboard::key_type>(key);
		e.key.scancode = scancode;
		e.key.modifiers = mods;

		data.events.push(e);
	}*/

	void glfw_window_maximize_callback(GLFWwindow *window, int maximnized)
	{
		auto& data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		data.minimized = false;
		data.maximized = true;

		auto e = event{};
		e.type = maximnized ? WINDOW_MAXIMIZED : WINDOW_RESTORED;

		data.events.push(e);
	}

	void glfw_window_scale_callback(GLFWwindow *window, float xscale, float yscale)
	{
		auto& data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		if (xscale == 0.f && yscale == 0.f)
		{
			data.maximized = false;
			data.minimized = true;
		}

		auto e = event{};
		e.type = WINDOW_RESCALED;
		e.scale = { xscale, yscale };

		data.events.push(e);
	}

	void glfw_window_scroll_input_callback(GLFWwindow *window, double xoffset, double yoffset)
	{
		auto& data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		auto e = event{};
		e.type = MOUSE_SCROLL_MOVED;
		e.scroll = { static_cast<float>(xoffset), static_cast<float>(yoffset) };

		data.events.push(e);
	}

	void glfw_window_size_callback(GLFWwindow *window, int width, int height)
	{
		auto& data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

		if (width == 0 && height == 0)
		{
			data.maximized = false;
			data.minimized = true;
		}

		auto e = event{};
		e.type = WINDOW_RESIZED;
		e.size = { static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height) };

		data.events.push(e);
	}

#ifdef AGL_DEBUG
	void glfw_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         AGL_CORE_EXCEPTION(ExOpenGL, message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       AGL_CORE_LOG_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          AGL_CORE_LOG_WARNING(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: AGL_CORE_LOG_TRACE(message); return;
		default: break;
		}
	}
#endif
}
