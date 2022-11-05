#pragma once
#include "agl/utility/type-unique-identifier.hpp"

namespace agl
{
	class uniform_prototyper;

	using uniform_type_uid = unique_type_id<uniform_prototyper>;
}