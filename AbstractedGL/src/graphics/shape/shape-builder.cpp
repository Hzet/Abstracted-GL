#include "agl/graphics/shape/shape-builder.hpp"

namespace agl
{
	void shape_builder::set_color(color const& c)
	{
		m_color = c;
	}

	color const& shape_builder::get_color() const
	{
		return m_color;
	}
}