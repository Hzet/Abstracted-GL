#include "core/app/input.hpp"
#include "core/app/application.hpp"

namespace agl
{
	bool input::key_pressed(key_type key)
	{
		auto* window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_handle());
		auto state = glfwGetKey(window, key);
		return state == GLFW_PRESS;
	}

	bool input::button_pressed(button_type button)
	{
		auto* window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_handle());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 input::get_mouse_position()
	{
		auto* window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_handle());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}
}