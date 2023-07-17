#pragma once
#include <glm/glm.hpp>

#include "agl/graphics/types/type-base.hpp"

namespace agl
{
	namespace detail
	{
		struct position {};
	}

	using position = base_type<detail::position, glm::vec3>;
}