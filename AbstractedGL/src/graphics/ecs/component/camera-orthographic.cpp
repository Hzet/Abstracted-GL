#include "graphics/ecs/component/camera-orthographic.hpp"

#include <glm/ext.hpp>

namespace agl
{
	void camera_orthographic::update_projection()
	{
		m_projection = glm::ortho(0.f, static_cast<float>(get_frame_dimensions().x), 0.f, static_cast<float>(get_frame_dimensions().y), get_planes().x, get_planes().y);
	}
}