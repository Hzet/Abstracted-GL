#include "agl/graphics/shape/shape-builder.hpp"

namespace agl
{
	std::vector<glm::vec4> shape_builder::get_colors(glm::vec4 const& c) const
	{
		return std::vector<glm::vec4>(get_vertex_count(), c);
	}

}