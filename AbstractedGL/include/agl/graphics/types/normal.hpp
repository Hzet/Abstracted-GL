#pragma once
#include <glm/glm.hpp>

#include "graphics/types/type-base.hpp"

namespace agl
{
	namespace detail
	{
		struct normal {};
	}

	using normal = base_type<detail::normal, glm::vec3>;
}