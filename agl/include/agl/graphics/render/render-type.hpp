#pragma once
#include "agl/core/app/resource-destructor.hpp"
#include "agl/core/app/resource-type-uid.hpp"

namespace agl
{
	struct render {};

	using render_type_destructor_base = resource_destructor_base<render>;

	template <typename T>
	using render_type_destructor = resource_destructor<render, T>;

	using render_type_uid = resource_type_uid<render>;
}

