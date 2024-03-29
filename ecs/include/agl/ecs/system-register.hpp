#pragma once
#include "agl/ecs/system-base.hpp"
#include "agl/ecs/registry.hpp"

namespace agl
{
	template <typename TGroupName, typename TDerived>
	class system_register
		: public system_base
	{
	public:
		using system_base::system_base;

		system_register();
		virtual ~system_register() = default;

	private:
		static bool register_type();

	private:
		static bool s_registered;

	private:
		virtual void register_me() const;
	};

#include "agl/ecs/system-register.inl"
}