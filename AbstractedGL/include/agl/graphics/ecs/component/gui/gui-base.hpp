#pragma once
#include "agl/graphics/ecs/component/gui/gui-uid.hpp"

namespace agl
{
	class gui_base
	{
	public:
		virtual ~gui_base() = default;

		gui_uid get_id() const;

	private:
		gui_uid m_id;
	};
}