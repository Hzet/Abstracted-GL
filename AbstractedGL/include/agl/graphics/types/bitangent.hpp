#pragma once
#include <glm/glm.hpp>

#include "graphics/types/type-base.hpp"

namespace agl
{
	namespace detail
	{
		struct bitangent{};
	}

	using bitangent = base_type<detail::bitangent, glm::vec3>;
}