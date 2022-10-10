#include "graphics/ecs/component/uniform/material.hpp"

namespace agl
{
	material_uniform::material_uniform()
	{
		shininess = create_member<float>("shininess");
		ambient = create_member<glm::vec4>("ambient");
		diffuse = create_member<glm::vec4>("diffuse");
		specular = create_member<glm::vec4>("specular");
		emission = create_member<glm::vec4>("emission");
	}
}