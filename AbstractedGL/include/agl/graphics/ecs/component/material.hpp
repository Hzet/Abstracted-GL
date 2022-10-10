#pragma once
#include <glm/glm.hpp>

namespace agl
{
	struct material
	{
		float shininess;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::vec4 emission;
	};
}