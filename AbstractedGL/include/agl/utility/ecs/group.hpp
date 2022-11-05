#pragma once
#include "agl/utility/ecs/group-base.hpp"

namespace agl
{
	template <typename TGroupName>
	class group
		: public group_base
	{
	public:
		using group_base::group_base;

		group();
	};

#include "agl/utility/ecs/group.inl"
}