#pragma once
#include <glm/glm.hpp>

#include "graphics/types/type-base.hpp"

namespace agl
{
	namespace detail
	{
		struct color 
		{
			static const glm::vec4 Black;
			static const glm::vec4 Blue;
			static const glm::vec4 Green;
			static const glm::vec4 Red;
			static const glm::vec4 White;
		};
	}

	using color = base_type<detail::color, glm::vec4>;
}