#include "agl/graphics/shape/shape-builder.hpp"

namespace agl
{
	shape_builder::shape_builder()
		: m_indexed{ false }
	{
	}

	bool shape_builder::is_indexed() const
	{
		return m_indexed;
	}

	void shape_builder::set_indexed(bool status)
	{
		m_indexed = status;
	}

	void shape_builder::set_color(color const& c)
	{
		m_color = c;
	}

	color const& shape_builder::get_color() const
	{
		return m_color;
	}
}