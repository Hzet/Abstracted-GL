#include "graphics/ecs/component/prism.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace agl
{
	static std::vector<position> produce_base(std::uint64_t side_count, glm::vec2 const& dimensions, float radius)
	{
		auto alpha = 360.f / side_count;
		auto const yaxis = glm::vec3{ 0.f, 1.f, 0.f };
		auto const vertex = glm::rotate(glm::vec3{ radius, 0.f, 0.f }, glm::radians(alpha / 2.f), yaxis);

		auto result = std::vector<position>{};
		result.reserve(side_count + 2);
		//result.reserve(3);

		result.push_back(vertex);
		result.push_back(glm::rotate(vertex, glm::radians(alpha), yaxis));
		result.push_back(glm::vec3{ 0.f });

		for (auto i = 3; i < side_count + 2; ++i)
		{
			alpha += std::fmod((360.f / side_count), 360.f);
			result.push_back(glm::rotate(vertex, glm::radians(alpha), yaxis));
		}

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
		m_mesh.draw_type = DRAW_TRIANGLE_STRIP;

		auto base = produce_base(m_sides_count, m_sides, m_radius);
		m_mesh.rbuffer.set_vertex_count(m_sides_count + 2);
		//m_mesh.rbuffer.set_vertex_count(3);
		m_mesh.rbuffer.add_vertices<position>(base.data());

		//for (auto& v : base)
		//	v->y += m_sides.y;
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