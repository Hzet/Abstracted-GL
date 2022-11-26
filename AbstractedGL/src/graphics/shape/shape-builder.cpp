#include "agl/graphics/shape/shape-builder.hpp"

namespace agl
{
	std::vector<color> shape_builder::get_colors(color const& c) const
	{
		return std::vector<color>(get_vertex_count(), c);
	}

}