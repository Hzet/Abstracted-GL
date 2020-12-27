#include "window-base.hpp"

#include "../System/error.hpp"
#include "../System/core-error-codes.hpp"

namespace agl
{
	static void windowSizeCallback(GLFWwindow *window, int width, int height)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::WINDOW_RESIZED;
		event.size = { static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height) };

		queue.push(event);
	}

	static void windowCloseCallback(GLFWwindow *window)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::WINDOW_CLOSED;

		queue.push(event);
	}

	static void windowFocusCallback(GLFWwindow *window, int focused)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = focused ? Event::WINDOW_GAINED_FOCUS : Event::WINDOW_LOST_FOCUS;

		queue.push(event);
	}

	static void windowMaximizeCallback(GLFWwindow *window, int maximnized)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = maximnized ? Event::WINDOW_MAXIMIZED : Event::WINDOW_RESTORED;

		queue.push(event);
	}

	static void windowIconifyCallback(GLFWwindow *window, int iconified)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = iconified ? Event::WINDOW_MINIMIZED : Event::WINDOW_RESTORED;

		queue.push(event);
	}

	static void windowScaleCallback(GLFWwindow *window, float xscale, float yscale)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::WINDOW_RESCALED;
		event.scale = { xscale, yscale };

		queue.push(event);
	}

	static void windowKeyInputCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		switch (action)
		{
		case GLFW_PRESS:
			event.type = Event::KEY_PRESSED;
			break;
		case GLFW_RELEASE:
			event.type = Event::KEY_RELEASED;
			break;
		case GLFW_REPEAT:
			event.type = Event::KEY_REPEATED;
			break;
		}

		event.key.code = static_cast<Keyboard::EKeycode>(key);
		event.key.scancode = scancode;
		event.key.modifiers = mods;

		queue.push(event);
	}

	static void windowCharCallback(GLFWwindow *window, unsigned int codepoint)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::TEXT_ENTERED;
		event.character = codepoint;

		queue.push(event);
	}

	static void windowCursorPosCallback(GLFWwindow *window, double xpos, double ypos)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::MOUSE_MOVED;
		event.position = { xpos, ypos };

		queue.push(event);
	}

	static void windowCursorEnterCallback(GLFWwindow *window, int entered)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = entered ? Event::MOUSE_ENTERED : Event::MOUSE_LEFT;

		queue.push(event);
	}

	static void windowButtonInputCallback(GLFWwindow *window, int button, int action, int mods)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		switch (action)
		{
		case GLFW_PRESS:
			event.type = Event::MOUSE_KEY_PRESSED;
			break;
		case GLFW_RELEASE:
			event.type = Event::MOUSE_KEY_RELEASED;
			break;
		}

		event.button.code = static_cast<Mouse::EButton>(button);
		event.button.bit_modifiers = mods;

		queue.push(event);
	}

	static void windowScrollInputCallback(GLFWwindow *window, double xoffset, double yoffset)
	{
		system::CEventQueue &queue = *reinterpret_cast<system::CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::MOUSE_SCROLL_MOVED;
		event.scroll = { xoffset, yoffset };

		queue.push(event);
	}

	static void windowFramebufferSizeCallback(GLFWwindow *window, int width, int height)
	{
		AGL_CALL(glViewport(0, 0, width, height));
	}

	static void GLFWerrorCallback(int error, const char *description)
	{
		AGL_CORE_ERROR("GLFW has failed!\nError code [{}] - {}", Error::GLFW_FAILURE, error, description);
	}

/*
	static void GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         AGL_CORE_LOG_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       AGL_CORE_LOG_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          AGL_CORE_LOG_WARNING(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: AGL_CORE_LOG_TRACE(message); return;
		}

		AGL_CORE_ASSERT(false, "Unknown severity level!");
	}*/

	
	std::size_t CWindowBase::WindowsCount_ = 0u;

	std::unordered_map<std::uint64_t, std::uint64_t> CWindowBase::WindowHints_ = {
		{GLFW_CONTEXT_VERSION_MAJOR, 3}, 
		{GLFW_CONTEXT_VERSION_MINOR, 3},
		{GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE}
	};

	CWindowBase CWindowBase::Create(const std::string &title, std::uint32_t width, std::uint32_t height)
	{
		if (WindowsCount_ == 0u)
		{
			if (!glfwInit())
				AGL_CORE_CRITICAL("Failed to initialize GLFW!", Error::GLFW_FAILURE);

			for (const auto &m : WindowHints_)
				glfwWindowHint(m.first, m.second);

			glfwSetErrorCallback(GLFWerrorCallback);
		}

		CWindowBase result(title, width, height);
		
		result.window_ = std::unique_ptr<GLFWwindow, SGLFWwindowDeleter>(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr));


		if (result.window_ == nullptr)
			AGL_CORE_CRITICAL("Failed to create a window!", Error::GLFW_FAILURE);

		glfwMakeContextCurrent(result.window_.get());

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			AGL_CORE_CRITICAL("Failed to initialize OpenGL context!", Error::GLAD_FAILURE);

/*
#ifdef AGL_DEBUG
		AGL_CALL(glEnable(GL_DEBUG_OUTPUT));
		AGL_CALL(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
		AGL_CALL(glDebugMessageCallback(GLDebugCallback, nullptr));
		AGL_CALL(glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE));

#endif*/

		glfwSetWindowUserPointer(result.window_.get(), reinterpret_cast<void*>(&result.queue_));

		result.setGLFWCallbacks();

		return result;
	}

	void CWindowBase::SetHint(const std::uint64_t hint, const std::uint64_t value)
	{
		WindowHints_[hint] = value;
	}

	CWindowBase::CWindowBase(const std::string &title, const std::uint32_t width, const std::uint32_t height)
		: title_(title),
		width_(width),
		height_(height)
	{
		WindowsCount_++;
	}

	CWindowBase::CWindowBase(CWindowBase &&other)
		: CMoveOnly(std::move(other)),
		title_(std::move(other.title_)),
		width_(std::move(other.width_)),
		height_(std::move(other.height_)),
		window_(std::move(other.window_)),
		queue_(std::move(other.queue_))
	{
		glfwSetWindowUserPointer(window_.get(), &queue_);
	}

	CWindowBase::~CWindowBase()
	{
		if (!isMoveConstructing())
			shutdown();
	}

	void CWindowBase::shutdown()
	{
		if (WindowsCount_ == 0u)
			return;

		WindowsCount_--;

		if (WindowsCount_ == 0u)
			glfwTerminate();
		else
			glfwDestroyWindow(window_.get());
	}

	bool CWindowBase::isOpen()
	{
		if (glfwWindowShouldClose(window_.get()))
		{
			shutdown();
			return false;
		}

		glfwPollEvents();
		glfwSwapBuffers(window_.get());

		return true;
	}

	void CWindowBase::close()
	{
		glfwSetWindowShouldClose(window_.get(), GLFW_TRUE);
	}

	bool CWindowBase::pollEvent(SEvent &event)
	{
		if (queue_.count() == 0)
			return false;

		event = queue_.pop();
		return true;
	}

	std::int32_t CWindowBase::getInputMode() const
	{
		return glfwGetInputMode(window_.get(), mode);
	}

	void CWindowBase::setInputMode(const std::int32_t mode, const std::int32_t value) const
	{
		glfwSetInputMode(window_.get(), mode, value);
	}

	void CWindowBase::setGLFWCallbacks()
	{
		glfwSetWindowSizeCallback(window_.get(), windowSizeCallback);

		glfwSetWindowCloseCallback(window_.get(), windowCloseCallback);

		glfwSetWindowFocusCallback(window_.get(), windowFocusCallback);

		glfwSetWindowMaximizeCallback(window_.get(), windowMaximizeCallback);

		glfwSetWindowIconifyCallback(window_.get(), windowIconifyCallback);

		glfwSetWindowContentScaleCallback(window_.get(), windowScaleCallback);

		glfwSetKeyCallback(window_.get(), windowKeyInputCallback);

		glfwSetCharCallback(window_.get(), windowCharCallback);

		glfwSetCursorPosCallback(window_.get(), windowCursorPosCallback);

		glfwSetCursorEnterCallback(window_.get(), windowCursorEnterCallback);

		glfwSetMouseButtonCallback(window_.get(), windowButtonInputCallback);

		glfwSetScrollCallback(window_.get(), windowScrollInputCallback);

		glfwSetFramebufferSizeCallback(window_.get(), windowFramebufferSizeCallback);
	}
}
