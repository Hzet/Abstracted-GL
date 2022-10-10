#pragma once
#include <glm/glm.hpp>

namespace agl
{
	struct directional_light
	{
		glm::vec4 ambient;
		glm::vec4 color;
		glm::vec4 diffuse;
		glm::vec3 direction;
		glm::vec4 specular;
	};
}