#pragma once
#include <glm/glm.hpp>

namespace agl
{
	struct spot_light
	{
		glm::vec4 ambient;
		glm::vec4 color;
		glm::vec2 cutOff; // inner, outer
		glm::vec4 diffuse;
		glm::vec3 direction;
		glm::vec3 range; // constant, linear, quadratic
		glm::vec4 specular;
	};
}