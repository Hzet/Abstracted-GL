#pragma once
#include "utility/ecs/group-base.hpp"

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

#include "utility/ecs/group.inl"
}