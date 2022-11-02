#pragma once
#include <glm/glm.hpp>

#include "graphics/types/type-base.hpp"

namespace agl
{
	namespace detail
	{
		struct color {};
	}

	using color = base_type<detail::color, glm::vec4>;
}