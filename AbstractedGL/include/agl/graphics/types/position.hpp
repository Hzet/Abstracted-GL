#pragma once
#include <glm/glm.hpp>

#include "agl/graphics/types/type-base.hpp"

namespace agl
{
	namespace detail
	{
		struct position {};
	}

	using position_3d = base_type<detail::position, glm::vec3>;
	using position_2d = base_type<detail::position, glm::vec2>;
}