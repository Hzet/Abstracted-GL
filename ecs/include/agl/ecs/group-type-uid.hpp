#pragma once
#include "agl/uid/type-unique-identifier.hpp"

namespace agl
{
	class group_base;

	using group_type_uid = unique_type_id<group_base>;
}