#include "agl/graphics/ecs/component/rectangle.hpp"

namespace agl
{
	mesh rectangle::create_mesh(glm::vec2 const& size)
	{
		auto result = mesh{};
		result.draw_type = DRAW_TRIANGLES;

		auto const vertices = std::vector<position>{ 
			{ 0.f, 0.f, 0.f },
			{ 0.f, size.y, 0.f },
			{ size.x, size.y, 0.f },
			{ size.x, size.y, 0.f },
			{ size.x, 0.f, 0.f },
			{ 0.f, 0.f, 0.f }
		};

		result.rbuffer.set_vertex_count(6);
		result.rbuffer.set_vertices(vertices);

		return result;
	}

	rectangle rectangle::create_data(glm::vec2 const& size)
	{
		auto result = rectangle{};
		result.size = size;

		return result;
	}

}