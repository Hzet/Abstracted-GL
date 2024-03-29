#pragma once
#include "agl/graphics/shader/uniform-base.hpp"
#include "agl/graphics/shader/uniform-prototyper.hpp"

namespace agl
{
	template <typename TName, typename... TComponents>
	class uniform_register
		: public uniform_base
	{
	public:
		using uniform_base::uniform_base;

		uniform_register(std::string const& name);
		virtual ~uniform_register() = default;
		
	private:
		static bool register_type();

		template <std::uint64_t... Sequence> static void register_type_impl(std::index_sequence<Sequence...>);

		static bool s_registered;

		virtual void register_me() const;
	};

#include "agl/graphics/shader/uniform-register.inl"
}