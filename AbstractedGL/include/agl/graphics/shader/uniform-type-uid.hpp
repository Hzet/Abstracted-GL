#pragma once
#include "utility/type-unique-identifier.hpp"

namespace agl
{
	class uniform_prototyper;

	template <typename TData>
	using TUniformDataTypeUID = TTypeUID<uniform_prototyper, TData>;

	using uniform_type_uid = TTypeUID<uniform_prototyper>;
}