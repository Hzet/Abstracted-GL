#include "agl/graphics/shape/rectangle.hpp"

namespace agl
{
	rectangle_builder::rectangle_builder(rectangle const& rect)
		: m_specification{ rect }
	{
	}

	std::vector<std::int32_t> rectangle_builder::get_indices() const
	{
		if (is_indexed())
			return std::vector<std::int32_t>{};

		return std::vector<std::int32_t>{
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
		if (is_indexed())
			return 4;
		return 6;
	}

	std::vector<position> rectangle_builder::get_positions() const
	{
		if (is_indexed())
		{
			return std::vector<position>{
				{0.f, 0.f, 0.f},										// left bottom
				{ 0.f, m_specification.size.y, 0.f },					// left top
				{ m_specification.size.x, m_specification.size.y, 0.f },// right top
				{ m_specification.size.x, 0.f, 0.f }					// right bottom
			};
		}

		return std::vector<position>{
			{ 0.f, 0.f, 0.f },										 // left bottom
			{ 0.f, m_specification.size.y, 0.f },					 // left top
			{ m_specification.size.x, m_specification.size.y, 0.f }, // right top
			{ 0.f, 0.f, 0.f },										 // left bottom
			{ m_specification.size.x, m_specification.size.y, 0.f }, // right top
			{ m_specification.size.x, 0.f, 0.f }					 // right bottom

		};
	}

	std::vector<color> rectangle_builder::get_colors() const
	{
		if (is_indexed())
			return std::vector<color>(get_vertex_count(), get_color());

		return std::vector<color>(get_vertex_count(), get_color());
	}

}