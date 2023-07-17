#pragma once
#include "agl/ecs/group-base.hpp"

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

#include "agl/ecs/group.inl"
}