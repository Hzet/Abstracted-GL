#pragma once
#include <cstdint>
#include <GLFW/glfw3.h>

namespace agl
{
	enum cursor_type : std::uint32_t 
	{
		CURSOR_NORMAL = GLFW_CURSOR_NORMAL,
		CURSOR_HIDDEN = GLFW_CURSOR_HIDDEN,
		CURSOR_DISABLED = GLFW_CURSOR_DISABLED
	};

	enum input_mode : std::uint32_t
	{
		INPUT_STICKY_BUTTONS = GLFW_STICKY_MOUSE_BUTTONS,
		INPUT_STICKY_KEYS = GLFW_STICKY_KEYS
	};
}

