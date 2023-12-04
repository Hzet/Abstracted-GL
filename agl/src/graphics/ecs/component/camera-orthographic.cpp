#include "agl/graphics/ecs/component/camera-orthographic.hpp"

#include <glm/ext.hpp>

namespace agl
{
	const transform& camera_orthographic::calc_projection()
	{
		if (m_projection_update)
		{
			m_projection = glm::ortho(-static_cast<float>(get_resolution().x) / 2.f, static_cast<float>(get_resolution().x) / 2.f,
				-static_cast<float>(get_resolution().y) / 2.f, static_cast<float>(get_resolution().y) / 2.f,
				get_planes().x, get_planes().y);

			m_projection_update = false;
		}

		return m_projection;
	}
}