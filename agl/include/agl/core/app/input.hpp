#pragma once
#include <glm/glm.hpp>
#include "agl/core/event-types.hpp"

namespace agl
{
	class input
	{
	public:
		static bool key_pressed(key_type key);
		static bool button_pressed(button_type button);
		static glm::vec2 get_mouse_position();
	};
}

