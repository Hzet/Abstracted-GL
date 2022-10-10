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
	
	struct color_base
	{
		static const color Black;
		static const color Blue;
		static const color Green;
		static const color Red;
		static const color White;
	};
}