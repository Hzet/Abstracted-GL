#pragma once
#include "utility/type-unique-identifier.hpp"

namespace agl
{
	class system_base;

	using system_type_uid = unique_type_id<system_base>;
}