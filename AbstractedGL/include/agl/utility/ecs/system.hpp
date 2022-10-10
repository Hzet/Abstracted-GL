#pragma once
#include "utility/ecs/system-object.hpp"

namespace agl
{
	template <typename ...Args> 
	class system;

	template <typename TDerived>
	class system<TDerived>
		: public system_object<registry_system::misc_group, TDerived>
	{
	public:
		using system_object<registry_system::misc_group, TDerived>::system_object;
	};

	template <typename TGroupName, typename TDerived>
	class system<TGroupName, TDerived>
		: public system_object<TGroupName, TDerived>
	{
	public:
		using system_object<TGroupName, TDerived>::system_object;
	};
}