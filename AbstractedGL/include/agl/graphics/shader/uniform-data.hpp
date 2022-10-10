#pragma once
#include "graphics/shader/uniform-base.hpp"

namespace agl
{
	template <typename TData>
	struct data_uniform
		: public uniform_base
	{
		virtual ~data_uniform() = default;

		TData data;
	};
}