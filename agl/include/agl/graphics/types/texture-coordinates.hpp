#pragma once
#include <glm/glm.hpp>

#include "agl/graphics/types/type-base.hpp"

namespace agl
{
	namespace detail
	{
		struct texture_position{};
	}

	using texture_position = base_type<detail::texture_position, glm::vec2>;
}