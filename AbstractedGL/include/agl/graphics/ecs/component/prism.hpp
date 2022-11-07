#pragma once
#include <glm/glm.hpp>
#include "agl/graphics/ecs/component/mesh.hpp"

namespace agl
{
	class prism
	{
	public:
		static mesh create_mesh(std::uint64_t sides_count, float radius, float height);
		static prism create_data(std::uint64_t sides_count, float radius, float height);

	public:
		float radius;
		std::uint64_t sides_count;
		glm::vec2 side_size;
	};
}