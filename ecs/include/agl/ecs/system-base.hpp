#pragma once
#include <memory>

#include "agl/ecs/system-type-uid.hpp"

namespace agl
{
	class registry;

	class system_base
	{
	public:
		system_base() = default;
		virtual ~system_base() = default;
		
		const system_type_uid& get_system_uid() const;

		virtual void init(registry &reg) = 0;
		virtual void update(registry &reg) = 0;
		
	protected:
		friend class group_base;

		system_base(system_type_uid systemUID);

	private:
		system_type_uid m_id_system;
	};
}