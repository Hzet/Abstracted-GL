#pragma once
#include <glm/glm.hpp>

#include "graphics/types/type-base.hpp"

namespace agl
{
	namespace detail
	{
		struct rotation {};
	}

	using rotation = base_type<detail::rotation, glm::vec3>;
}