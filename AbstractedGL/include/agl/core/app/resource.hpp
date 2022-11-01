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
	
	using resource_type_uid = unique_type_id<resource_base>;
	
}

