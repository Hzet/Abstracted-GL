#include "agl/graphics/ecs/component/prism.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace agl
{
	static std::vector<std::uint32_t> produce_indices(std::uint64_t side_count);
	static std::vector<position> produce_vertices(std::uint64_t side_count, float radius, float height);
	

	mesh prism::create_mesh(std::uint64_t sides_count, float radius, float height)
	{
		auto data = create_data(sides_count, radius, height);

		auto result = mesh{};

		result.draw_type = DRAW_TRIANGLES;
		auto const vertices = produce_vertices(data.sides_count, data.radius, data.side_size.y);
		auto const indices = produce_indices(data.sides_count);

		result.rbuffer.set_vertex_count(data.sides_count * 2 + 2);
		result.rbuffer.set_vertices(vertices.data());
		result.rbuffer.add_indices(indices.data(), indices.size());

		return result;
	}

	prism prism::create_data(std::uint64_t sides_count, float radius, float height)
	{
		auto const alpha = 360.f / sides_count;
		auto result = prism{};
		auto const yaxis = glm::vec3{ 0.f, 1.f, 0.f };

		result.radius = radius;
		result.sides_count = sides_count;
		result.side_size.x = glm::distance(glm::vec3{}, glm::rotate(glm::vec3{ radius, 0.f, 0.f }, glm::radians(alpha), yaxis));
		result.side_size.y = height;

		return result;
	}

	static std::vector<position> produce_vertices(std::uint64_t side_count, float radius, float height)
	{
		auto alpha = 360.f / side_count;
		auto const yaxis = glm::vec3{ 0.f, 1.f, 0.f };
		auto result = std::vector<position>{};

		// create top base
		result.push_back(glm::vec3{ 0.f });
		for (auto i = 0; i < side_count; ++i)
		{
			auto const vertex = glm::rotate(glm::vec3{ radius, 0.f, 0.f }, glm::radians(alpha * i), yaxis);
			result.push_back(vertex);
		}

		// create bottom base
		for (auto i = 0; i <= side_count; ++i)
		{
			auto const vertex = result[i];
			result.push_back(glm::vec3{ vertex->x, -height, vertex->z });
		}

		return result;
	}

	static std::vector<std::uint32_t> produce_indices(std::uint64_t side_count)
	{
		auto result = std::vector<std::uint32_t>{};
		result.reserve(side_count * 12);

		// index top base
		for (auto i = 0; i < side_count - 1; ++i)
		{
			result.push_back(0);
			result.push_back(i + 1);
			result.push_back(i + 2);
		}

		result.push_back(0);
		result.push_back(side_count);
		result.push_back(1);

		// index sides
		for (auto i = 0; i < side_count - 1; ++i)
		{
			auto const offset_a = (i % 2) * (side_count + 5);

			result.push_back(i + 1);
			result.push_back(i + 2);
			result.push_back(i + side_count + 2);

			result.push_back(i + side_count + 2);
			result.push_back(i + side_count + 3);
			result.push_back(i + 2);
		}

		result.push_back(side_count);
		result.push_back(1);
		result.push_back(side_count * 2 + 1);

		result.push_back(side_count * 2 + 1);
		result.push_back(side_count + 2);
		result.push_back(1);

		// index bottom base
		for (auto i = 0; i < side_count - 1; ++i)
		{
			result.push_back(side_count + 1);
			result.push_back(side_count + i + 2);
			result.push_back(side_count + i + 3);
		}

		result.push_back(side_count + 1);
		result.push_back(side_count * 2 + 1);
		result.push_back(side_count + 2);

		return result;
	}
}