#pragma once
#include "utility/type-unique-identifier.hpp"

namespace agl
{
	class resource_base
	{
	public:
		resource_base() = default;
		resource_base(resource_base&&) = default;
		resource_base& operator=(resource_base&&) = default;
		resource_base(resource_base const&) = delete;
		resource_base& operator=(resource_base const&) = delete;
		virtual ~resource_base() = default;

	protected:
		virtual void dummy() const = 0;
	};
	
	template <typename T>
	using TResourceTypeUID = TTypeUID<resource_base, T>;

	using resource_type_uid = TTypeUID<resource_base>;
	
}

