#pragma once
#include "utility/type-unique-identifier.hpp"

namespace agl
{
	class group_base;

	template <typename T>
	using TGroupTypeUID = TTypeUID<group_base, T>;

	using group_type_uid = TTypeUID<group_base>;
}