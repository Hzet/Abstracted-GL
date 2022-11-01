#pragma once
#include <vector>

#include "graphics/shader/uniform-wrapper.hpp"
#include "graphics/shader/uniform-type-uid.hpp"
#include "utility/ecs/component-type-uid.hpp"

namespace agl
{
	class group_uniform
	{
	public:
		static std::unique_ptr<uniform_base> get_uniform(uniform_type_uid id_uniform, component_type_uid id_component_type, uniform_base *dataSource = nullptr);

	private:
		template <typename TData, typename... TComponents>
		friend class register_uniform;

	private:
		template <typename TData, typename TComponent> static void add_uniform();

		static std::uint64_t get_index(uniform_type_uid id_uniform);

	private:
		static std::vector<std::vector<std::unique_ptr<uniform_wrapper_base>>>& get_groups();
	};

#include "graphics/shader/uniform-group.inl"
}

