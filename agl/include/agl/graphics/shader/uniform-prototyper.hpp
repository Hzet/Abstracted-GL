#pragma once
#include <vector>

#include "agl/graphics/shader/uniform-wrapper.hpp"
#include "agl/graphics/shader/uniform-type-uid.hpp"
#include "agl/ecs/component-type-uid.hpp"

namespace agl
{
	class uniform_prototyper
	{
	public:
		static std::unique_ptr<uniform_base> get_prototype(uniform_type_uid id_uniform, component_type_uid id_component_type, uniform_base *dataSource = nullptr);

	private:
		template <typename TName, typename... TComponents>
		friend class uniform_register;

	private:
		template <typename TName, typename TComponent> static void add_prototype();

		static std::uint64_t get_index(uniform_type_uid id_uniform);

	private:
		static std::vector<std::vector<std::unique_ptr<uniform_wrapper_base>>>& get_groups();
	};

#include "agl/graphics/shader/uniform-prototyper.inl"
}

