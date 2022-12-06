#include "agl/graphics/ecs/component/camera-orthographic.hpp"

#include <glm/ext.hpp>

namespace agl
{
	void camera_orthographic::update_projection()
	{
		m_projection = glm::ortho(-static_cast<float>(get_resolution().x) / 2.f, static_cast<float>(get_resolution().x) / 2.f,
								  -static_cast<float>(get_resolution().y) / 2.f, static_cast<float>(get_resolution().y) / 2.f, 
								  get_planes().x, get_planes().y);
	}
}