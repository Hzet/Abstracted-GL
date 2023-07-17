#pragma once
#include <vector>
#include <memory>

#include "agl/ecs/system-base.hpp"
#include "agl/ecs/group-type-uid.hpp"

namespace agl
{
	class group_base
	{
	public:
		group_base() = default;
		group_base(group_base&&) = default;
		group_base(const group_base&) = delete;
		group_base& operator=(group_base&&) = default;
		group_base& operator=(const group_base&) = delete;
		virtual ~group_base() = default;

		template <typename T>
		void add_system();

		void init(registry &reg);
		void update(registry &reg);

		const group_type_uid& getGroupUID() const;

	protected:
		group_base(group_type_uid id_group);

	private:
		group_type_uid m_id_group;
		std::vector<std::unique_ptr<system_base>> m_systems;
	};

	template <typename T>
	void group_base::add_system()
	{
		m_systems.push_back(std::make_unique<T>());
	}
}