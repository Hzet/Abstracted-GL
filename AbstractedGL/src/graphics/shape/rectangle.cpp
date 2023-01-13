#include "agl/graphics/shape/rectangle.hpp"

namespace agl
{
	rectangle_builder::rectangle_builder(rectangle const& rect)
		: m_specification{ rect }
	{
	}

	std::vector<std::uint32_t> rectangle_builder::get_indices() const
	{
		return std::vector<std::uint32_t>{
			0, 1, 2, 
			0, 2, 3
		};
	}

	gl_draw_type rectangle_builder::get_draw_type() const
	{
		return DRAW_TRIANGLES;
	}

	std::uint64_t rectangle_builder::get_vertex_count() const
	{
		return 4;
	}

	std::uint64_t rectangle_builder::get_index_count() const
	{
		return 6;
	}

	std::vector<glm::vec2> rectangle_builder::get_positions() const
{
		return std::vector<glm::vec2>{
			{ 0.f, 0.f },										// left bottom
			{ 0.f, m_specification.size.y },					// left top
			{ m_specification.size.x, m_specification.size.y }, // right top
			{ m_specification.size.x, 0.f }					    // right bottom
		};
	}
}