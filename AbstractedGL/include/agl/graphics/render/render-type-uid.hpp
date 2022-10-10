#pragma once
#include "utility/type-unique-identifier.hpp"

namespace agl
{
	struct render {};

	template <typename T>
	using TRenderTypeUID = TTypeUID<render, T>;

	using render_type_uid = TTypeUID<render>;
}

