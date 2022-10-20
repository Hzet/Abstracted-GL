#pragma once
#include <vector>

#include "graphics/shader/uniform-wrapper.hpp"
#include "graphics/shader/uniform-type-uid.hpp"
#include "utility/ecs/component-type-uid.hpp"

namespace agl
{
	class uniform_prototyper
	{
	private:
		struct group
		{
			uniform_type_uid id_uniform_type;
			std::vector<std::unique_ptr<uniform_wrapper_base>> prototypes;
		};

	public:
		template <typename TName, typename TComponent>
		static void add_prototype();

		static std::unique_ptr<uniform_base> get_prototype(uniform_type_uid id_uniform_type, component_type_uid id_component, uniform_base* source = nullptr);

		static std::unique_ptr<uniform_base> get_prototype(uniform_type_uid id_uniform_type);

		static std::vector<component_type_uid> get_prototype_components(uniform_type_uid id_uniform_type);

	private:
		static std::uint64_t get_group_index(uniform_type_uid id_uniform_type);

	private:
		static std::vector<group>& get_groups();
	};


	/*class group_uniform
	{
	public:
		template <typename TName> static const group_uniform& get_group();
		static const group_uniform& get_group(uniform_type_uid id_uniform_type);
		
		group_uniform() = default;
		group_uniform(group_uniform &&other) = default;
		group_uniform(const group_uniform &other) = delete;
		group_uniform& operator=(group_uniform &&other) = default;
		group_uniform& operator=(const group_uniform &other) = delete;

		std::uint64_t get_count() const;

		const uniform_base& operator[](std::uint64_t index) const;

		std::unique_ptr<uniform_base> get_uniform(component_type_uid id_component_type, uniform_base *dataSource = nullptr) const;

	private:
		friend class manager;

		class manager
		{
		public:
			template <typename TName, typename TComponent> void add_uniform();
			group_uniform& get_group(uniform_type_uid id_uniform_type);

		private:
			static std::uint64_t get_index(uniform_type_uid id_uniform_type);

			std::vector<group_uniform> m_groups;
		};

		template <typename TName, typename... TComponents>
		friend class register_uniform;

		template <typename TName, typename TComponent> static void add_uniform();

		static manager& get_manager();

		std::vector<std::unique_ptr<uniform_wrapper_base>> m_prototypes;
	};*/

#include "graphics/shader/uniform-group.inl"
}

