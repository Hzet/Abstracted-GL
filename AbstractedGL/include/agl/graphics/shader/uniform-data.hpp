#pragma once
#include "graphics/shader/uniform-base.hpp"

namespace agl
{
	template <typename TData>
	class data_uniform
		: public uniform_base
	{
	public:
		using uniform_base::uniform_base;

		data_uniform(std::string const& name = "");
		virtual ~data_uniform() = default;

		TData data;
	};

	template <typename TData>
	data_uniform<TData>::data_uniform(std::string const& name)
		: uniform_base{ name }
	{
	}
}