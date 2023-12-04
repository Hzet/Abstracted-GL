#pragma once
#include "agl/uid/type-unique-identifier.hpp"

namespace agl
{
	template <typename TName>
	using resource_type_uid = unique_type_id<TName>;
}