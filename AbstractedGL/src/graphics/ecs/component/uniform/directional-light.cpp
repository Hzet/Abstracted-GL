#pragma once
#include "graphics/ecs/component/uniform/directional-light.hpp"

namespace agl
{

	std::unique_ptr<agl::uniform_member<std::int32_t>> directional_light_uniform::s_count = std::int32_t{ 0 };

	directional_light_uniform::directional_light_uniform()
	{
		++(*(*s_count));

		ambient = create_member<glm::vec4>("ambient");
		color = create_member<glm::vec4>("color");
		diffuse = create_member<glm::vec4>("diffuse");
		direction = create_member<glm::vec3>("direction");
		specular = create_member<glm::vec4>("specular");
	}

	directional_light_uniform::~directional_light_uniform()
	{
		--(*(*s_count));
	}

	std::int32_t directional_light_uniform::get_count()
	{
		return *(*s_count);
	}

}