#pragma once
#include "utility/type-unique-identifier.hpp"

namespace agl
{
	class group_uniform;

	template <typename TData>
	using TUniformDataTypeUID = TTypeUID<group_uniform, TData>;

	using uniform_data_type_uid = TTypeUID<group_uniform>;
}