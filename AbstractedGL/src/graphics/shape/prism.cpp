#include "agl/graphics/shape/prism.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/ext.hpp>

namespace agl
{
	prism_builder::prism_builder(std::uint64_t sides_count, float radius, float height)
	{
		auto const alpha = 360.f / sides_count;
		auto const yaxis = glm::vec3{ 0.f, 1.f, 0.f };

		m_specification.radius = radius;
		m_specification.side_count = sides_count;
		m_specification.side_size.x = glm::distance(glm::vec3{}, glm::rotate(glm::vec3{ radius, 0.f, 0.f }, glm::radians(alpha), yaxis));
		m_specification.side_size.y = height;
	}

	gl_draw_type prism_builder::get_draw_type() const
	{
		return DRAW_TRIANGLES;
	}

	std::uint64_t prism_builder::get_vertex_count() const
	{
		return (m_specification.side_count + 1) * 2;
	}

	std::uint64_t prism_builder::get_index_count() const
	{
		return m_specification.side_count * 12;
	}

	std::vector<std::uint32_t> prism_builder::get_indices() const
	{
		auto result = std::vector<std::uint32_t>{};
		result.reserve(get_index_count());

		// index top base
		for (auto i = 0; i < m_specification.side_count - 1; ++i)
		{
			result.push_back(0);
			result.push_back(i + 1);
			result.push_back(i + 2);
		}

		result.push_back(0);
		result.push_back(m_specification.side_count);
		result.push_back(1);

		// index sides
		for (auto i = 0; i < m_specification.side_count - 1; ++i)
		{
			auto const offset_a = (i % 2) * (m_specification.side_count + 5);

			result.push_back(i + 1);
			result.push_back(i + 2);
			result.push_back(i + m_specification.side_count + 2);

			result.push_back(i + m_specification.side_count + 2);
			result.push_back(i + m_specification.side_count + 3);
			result.push_back(i + 2);
		}

		result.push_back(m_specification.side_count);
		result.push_back(1);
		result.push_back(m_specification.side_count * 2 + 1);

		result.push_back(m_specification.side_count * 2 + 1);
		result.push_back(m_specification.side_count + 2);
		result.push_back(1);

		// index bottom base
		for (auto i = 0; i < m_specification.side_count - 1; ++i)
		{
			result.push_back(m_specification.side_count + 1);
			result.push_back(m_specification.side_count + i + 2);
			result.push_back(m_specification.side_count + i + 3);
		}

		result.push_back(m_specification.side_count + 1);
		result.push_back(m_specification.side_count * 2 + 1);
		result.push_back(m_specification.side_count + 2);

		return result;
	}

	std::vector<position> prism_builder::get_positions() const
	{
		auto alpha = 360.f / m_specification.side_count;
		auto const yaxis = glm::vec3{ 0.f, 1.f, 0.f };
		auto result = std::vector<position>{};

		// create top base
		result.push_back(glm::vec3{ 0.f });
		for (auto i = 0; i < m_specification.side_count; ++i)
		{
			auto const vertex = glm::rotate(glm::vec3{ m_specification.radius, 0.f, 0.f }, glm::radians(alpha * i), yaxis);
			result.push_back(vertex);
		}

		// create bottom base
		for (auto i = 0; i <= m_specification.side_count; ++i)
		{
			auto const vertex = result[i];
			result.push_back(glm::vec3{ vertex->x, -m_specification.side_size.y, vertex->z });
		}

		return result;
	}

	std::vector<color> prism_builder::get_colors() const
	{
		return std::vector<color>(get_vertex_count(), get_color());
	}
}