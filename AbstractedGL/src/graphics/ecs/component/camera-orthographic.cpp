#include "graphics/ecs/component/camera-orthographic.hpp"

#include <glm/ext.hpp>

namespace agl
{
	void camera_orthographic::update_projection()
	{
		m_projection = glm::ortho(-static_cast<float>(get_frame_dimensions().x) / 2.f, static_cast<float>(get_frame_dimensions().x) / 2.f,
								  -static_cast<float>(get_frame_dimensions().y) / 2.f, static_cast<float>(get_frame_dimensions().y) / 2.f, 
								  get_planes().x, get_planes().y);
	}
}