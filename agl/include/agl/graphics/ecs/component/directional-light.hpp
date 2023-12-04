#pragma once
#include <glm/glm.hpp>

namespace agl
{
	struct directional_light
	{
		glm::vec4 ambient;
		glm::vec4 color;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};
}