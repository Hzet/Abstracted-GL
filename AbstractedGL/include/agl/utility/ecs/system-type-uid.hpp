#pragma once
#include "utility/type-unique-identifier.hpp"

namespace agl
{
	class system_base;

	template <typename T> 
	using TSystemTypeUID = TTypeUID<system_base, T>;

	using system_type_uid = TTypeUID<system_base>;
}