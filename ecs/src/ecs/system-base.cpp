#include "agl/ecs/system-base.hpp"

namespace agl
{
	system_base::system_base(system_type_uid systemUID)
		: m_id_system(systemUID)
	{
	}

	const system_type_uid& system_base::get_system_uid() const 
	{
		return m_id_system;
	}

}