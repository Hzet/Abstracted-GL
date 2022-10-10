#pragma once
#include "utility/type-unique-identifier.hpp"

namespace agl
{
	class component_base
	{};

	template <typename T>
	using TComponentTypeUID = TTypeUID<component_base, T>;
	
	using component_type_uid = TTypeUID<component_base>;
}