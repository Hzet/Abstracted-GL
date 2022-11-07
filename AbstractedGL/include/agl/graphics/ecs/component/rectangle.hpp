#pragma once
#include <glm/glm.hpp>
#include "agl/graphics/ecs/component/mesh.hpp"

namespace agl
{
	class rectangle
	{
	public:
		static mesh create_mesh(glm::vec2 const& size);
		static rectangle create_data(glm::vec2 const& size);

	public:
		glm::vec2 size;
	};
}