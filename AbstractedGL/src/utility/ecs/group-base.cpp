#include "agl/utility/ecs/group-base.hpp"

namespace agl
{
	void group_base::init(registry &reg)
	{
		for (auto &v : m_systems)
			v->init(reg);
	}

	void group_base::update(registry &reg)
	{
		for (auto &v : m_systems)
			v->update(reg);
	}

	const group_type_uid& group_base::getGroupUID() const
	{
		return m_id_group;
	}

	group_base::group_base(group_type_uid id_group)
		: m_id_group(id_group)
	{
	}
}