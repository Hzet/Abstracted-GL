#pragma once
#include <glm/glm.hpp>
#include <string>
#include <queue>

#include "core/event.hpp"

namespace agl
{
	struct window_data
	{
		bool closed;
		glm::vec2 contentScale;
		std::queue<event> events;
		glm::ivec2 framebufferSize;
		bool focused;
		bool maximized;
		bool minimized;
		glm::vec2 resolution;
		std::string title;
	};
}

