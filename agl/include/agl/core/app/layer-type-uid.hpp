#pragma once
#include "agl/uid/type-unique-identifier.hpp"

namespace agl
{
	class layer_base;

	using layer_type_uid = unique_type_id<layer_base>;
}