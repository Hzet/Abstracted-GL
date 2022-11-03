#pragma once
#include <glm/glm.hpp>

namespace agl
{
	struct spot_light
	{
		glm::vec4 ambient;
		glm::vec4 color;
		glm::vec2 cut_off; // inner, outer
		glm::vec4 diffuse;
		glm::vec3 range; // constant, linear, quadratic
		glm::vec4 specular;
	};
}