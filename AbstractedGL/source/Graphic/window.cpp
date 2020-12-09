#include "window.hpp"

#include "../System/error.hpp"
#include "../System/core-error-codes.hpp"

namespace agl
{
	static void windowSizeCallback(GLFWwindow *window, int width, int height)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::WINDOW_RESIZED;
		event.size = { static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height) };

		queue.push(event);
	}

	static void windowCloseCallback(GLFWwindow *window)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::WINDOW_CLOSED;

		queue.push(event);
	}

	static void windowFocusCallback(GLFWwindow *window, int focused)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = focused ? Event::WINDOW_GAINED_FOCUS : Event::WINDOW_LOST_FOCUS;

		queue.push(event);
	}

	static void windowMaximizeCallback(GLFWwindow *window, int maximnized)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = maximnized ? Event::WINDOW_MAXIMIZED : Event::WINDOW_RESTORED;

		queue.push(event);
	}

	static void windowIconifyCallback(GLFWwindow *window, int iconified)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = iconified ? Event::WINDOW_MINIMIZED : Event::WINDOW_RESTORED;

		queue.push(event);
	}

	static void windowScaleCallback(GLFWwindow *window, float xscale, float yscale)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::WINDOW_RESCALED;
		event.scale = { xscale, yscale };

		queue.push(event);
	}

	static void windowKeyInputCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

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

		event.key.code = static_cast<Event::EKeycode>(key);
		event.key.scancode = scancode;
		event.key.modifiers = mods;

		queue.push(event);
	}

	static void windowCharCallback(GLFWwindow *window, unsigned int codepoint)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::TEXT_ENTERED;
		event.character = codepoint;

		queue.push(event);
	}

	static void windowCursorPosCallback(GLFWwindow *window, double xpos, double ypos)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::MOUSE_MOVED;
		event.position = { xpos, ypos };

		queue.push(event);
	}

	static void windowCursorEnterCallback(GLFWwindow *window, int entered)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = entered ? Event::MOUSE_ENTERED : Event::MOUSE_LEFT;

		queue.push(event);
	}

	static void windowButtonInputCallback(GLFWwindow *window, int button, int action, int mods)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

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

		event.button.code = static_cast<Event::EButton>(button);
		event.button.bit_modifiers = mods;

		queue.push(event);
	}

	static void windowScrollInputCallback(GLFWwindow *window, double xoffset, double yoffset)
	{
		CEventQueue &queue = *reinterpret_cast<CEventQueue*>(glfwGetWindowUserPointer(window));

		SEvent event;
		event.type = Event::MOUSE_SCROLL_MOVED;
		event.scroll = { xoffset, yoffset };

		queue.push(event);
	}

	static void windowFramebufferSizeCallback(GLFWwindow *window, int width, int height)
	{
		AGL_CALL(glViewport(0, 0, width, height));
	}

	static void errorCallback(int error, const char *description)
	{
		AGL_CORE_ERROR("GLFW has failed!\nError code [{}] - {}", error, description);
	}

/*
	static void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         AGL_CORE_LOG_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       AGL_CORE_LOG_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          AGL_CORE_LOG_WARNING(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: AGL_CORE_LOG_TRACE(message); return;
		}

		AGL_CORE_ASSERT(false, "Unknown severity level!");
	}
*/
	
	std::size_t CWindow::WindowsCount_ = 0u;

	CWindow CWindow::Create(const std::string &title, std::uint32_t width, std::uint32_t height)
	{
		if (WindowsCount_ == 0u)
		{
			if (!glfwInit())
				AGL_CORE_CRITICAL("Failed to initialize GLFW!");

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			glfwSetErrorCallback(errorCallback);

#ifdef AGL_DEBUG
/*
			glEnable(GL_DEBUG_OUTPUT); 
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
			glDebugMessageCallback(GLDebugMessageCallback, nullptr); 
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
*/
#endif
		}

		CWindow result(title, width, height);
		
		result.window_ = std::unique_ptr<GLFWwindow, SGLFWwindowDeleter>(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr));


		if (result.window_ == nullptr)
			AGL_CORE_CRITICAL("Failed to create a window!");

		glfwMakeContextCurrent(result.window_.get());

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			AGL_CORE_CRITICAL("Failed to initialize OpenGL context!");

		glfwSetWindowUserPointer(result.window_.get(), reinterpret_cast<void*>(&result.queue_));

		// set event callback functions
		glfwSetWindowSizeCallback(result.window_.get(), windowSizeCallback);

		glfwSetWindowCloseCallback(result.window_.get(), windowCloseCallback);

		glfwSetWindowFocusCallback(result.window_.get(), windowFocusCallback);

		glfwSetWindowMaximizeCallback(result.window_.get(), windowMaximizeCallback);

		glfwSetWindowIconifyCallback(result.window_.get(), windowIconifyCallback);

		glfwSetWindowContentScaleCallback(result.window_.get(), windowScaleCallback);

		glfwSetKeyCallback(result.window_.get(), windowKeyInputCallback);

		glfwSetCharCallback(result.window_.get(), windowCharCallback);

		glfwSetCursorPosCallback(result.window_.get(), windowCursorPosCallback);

		glfwSetCursorEnterCallback(result.window_.get(), windowCursorEnterCallback);

		glfwSetMouseButtonCallback(result.window_.get(), windowButtonInputCallback);

		glfwSetScrollCallback(result.window_.get(), windowScrollInputCallback);

		glfwSetFramebufferSizeCallback(result.window_.get(), windowFramebufferSizeCallback);

		return result;
	}

	CWindow::CWindow(const std::string &title, std::uint32_t width, std::uint32_t height)
		: close_(false),
		move_(false),
		title_(title),
		width_(width),
		height_(height)
	{
		WindowsCount_++;
	}

	CWindow::CWindow(CWindow &&other)
		: close_(std::move(other.close_)),
		move_(false),
		title_(std::move(other.title_)),
		width_(std::move(other.width_)),
		height_(std::move(other.height_)),
		window_(std::move(other.window_)),
		queue_(std::move(other.queue_))
	{
		other.move_ = true;

		glfwSetWindowUserPointer(window_.get(), &queue_);
	}

	void CWindow::shutdown()
	{
		if (WindowsCount_ == 0u)
			return;

		WindowsCount_--;

		if (WindowsCount_ == 0u)
			glfwTerminate();
		else
			glfwDestroyWindow(window_.get());
	}

	CWindow::~CWindow()
	{
		if(!move_)
			shutdown();
	}

	bool CWindow::isOpen()
	{
		const bool result = !glfwWindowShouldClose(window_.get()) && !close_; // false if should close

		if (result)
		{
			glfwPollEvents();
			glfwSwapBuffers(window_.get());

			return true;
		}

		shutdown();

		return false;
	}

	void CWindow::close()
	{
		close_ = true;
	}

	bool CWindow::pollEvent(SEvent &event)
	{
		if (queue_.count() == 0)
			return false;

		event = queue_.pop();
		return true;
	}
}
