#pragma once
#include "agl/core/app/resource.hpp"

namespace agl
{
	class app_resource_base {};

	using app_resource = resource<app_resource_base>;

	using app_resource_type_uid = resource_type_uid<app_resource_base>;
}

