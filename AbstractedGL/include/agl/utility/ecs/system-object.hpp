#pragma once
#include "utility/ecs/system-base.hpp"
#include "utility/ecs/registry.hpp"

namespace agl
{
	template <typename TGroupName, typename TDerived>
	class system_object
		: public system_base
	{
	public:
		using system_base::system_base;

		system_object();
		virtual ~system_object() = default;

	private:
		static bool Register_;

		virtual void register_me() const;

		virtual std::unique_ptr<system_base> clone() const;
	};

#include "utility/ecs/system-object.inl"
}