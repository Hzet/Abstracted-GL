#pragma once
#include <vector>
#include <memory>

#include "agl/utility/ecs/system-base.hpp"
#include "agl/utility/ecs/group-type-uid.hpp"

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

		void add_system(const system_base &sys);

		void init(registry &reg);
		void update(registry &reg);

		const group_type_uid& getGroupUID() const;

	protected:
		group_base(group_type_uid id_group);

	private:
		group_type_uid m_id_group;
		std::vector<std::unique_ptr<system_base>> m_systems;
	};
}