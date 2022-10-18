#pragma once
#include "graphics/shader/uniform-data.hpp"
#include "graphics/shader/uniform-group.hpp"

namespace agl
{
	template <typename TData, typename... TComponents>
	class register_uniform
		: public data_uniform<TData>
	{
	public:
		using data_uniform<TData>::data_uniform;

		register_uniform(std::string const& name);
		virtual ~register_uniform() = default;
		
	private:
		static bool register_type();

		template <std::uint64_t... Sequence> static void register_type_impl(std::index_sequence<Sequence...>);

		static bool s_registered;

		virtual void register_me() const;
	};

#include "graphics/shader/uniform-register.inl"
}