#pragma once
#include <glm/glm.hpp>

#include "graphics/types/type-base.hpp"

namespace agl
{
	namespace detail
	{
		struct tangent {};
	}

	using tangent = base_type<detail::tangent, glm::vec3>;
}