#pragma once
#include "agl/utility/type-unique-identifier.hpp"

namespace agl
{
	class component_base
	{};

	using component_type_uid = unique_type_id<component_base>;
}