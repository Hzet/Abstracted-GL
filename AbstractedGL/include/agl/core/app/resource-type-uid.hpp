#pragma once
#include "agl/uid/type-unique-identifier.hpp"

namespace agl
{
	class resource;

	using resource_type_uid = unique_type_id<resource>;
}