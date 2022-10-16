#include "graphics/ecs/component/prism.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace agl
{
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

	prism::prism(shader_uid id_shader)
	{
		m_mesh.id_shader = id_shader;
	}

	void prism::set_radius(float radius)
	{
		m_radius = radius;
	}

	float prism::get_radius() const
	{
		return m_radius;
	}

	void prism::set_height(float height)
	{
		set_sides(glm::vec2{ 0.f, height});
	}

	float prism::get_height() const
	{
		return m_sides.y;
	}

	void prism::set_width(float width)
	{
		set_sides(glm::vec2{ width, 0.f });
	}

	float prism::get_width() const
	{
		return m_sides.x;
	}

	void prism::set_sides(glm::vec2 const& sides)
	{
		m_sides = sides;
		m_mesh.draw_type = DRAW_TRIANGLES;

		auto const vertices = produce_vertices(m_sides_count, m_radius, m_sides.y);
		auto const indices = produce_indices(m_sides_count);

		m_mesh.rbuffer.set_vertex_count(m_sides_count * 2 + 2);
		m_mesh.rbuffer.add_vertices(vertices.data());
		m_mesh.rbuffer.add_indices(indices.data(), indices.size());
	}

	glm::vec2 const& prism::get_sides() const
	{
		return m_sides;
	}

	void prism::set_side_count(float count)
	{
		m_sides_count = count;
	}

	float prism::get_side_count() const
	{
		return m_sides_count;
	}
	void prism::set_color(agl::color const& color)
	{
		auto vcolor = std::vector<agl::color>{};
		vcolor.reserve(m_mesh.rbuffer.get_vertex_count());

		for (auto i = 0; i < m_mesh.rbuffer.get_vertex_count(); ++i)
			vcolor.push_back(color);

		m_mesh.rbuffer.add_vertices(vcolor.data());
	}

	shader_uid prism::get_shader_uid() const
	{
		return m_mesh.id_shader;
	}

	void prism::set_shader_uid(shader_uid id_shader)
	{
		m_mesh.id_shader = id_shader;
	}

	uniform_array & prism::get_uniforms()
	{
		return m_mesh.uniforms;
	}
}