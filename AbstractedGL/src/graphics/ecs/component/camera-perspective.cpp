#include "agl/graphics/ecs/component/camera-perspective.hpp"

#include <glm/ext.hpp>

namespace agl
{
	camera_perspective::camera_perspective()
		: m_fov(45.f)
	{
	}

	float camera_perspective::get_fov() const
	{
		return m_fov;
	}

	void camera_perspective::set_fov(float fov)
	{
		m_needs_update = true;
	
		if (fov < 0.f)
			fov = 0.f;
		else if (fov >= 179.f)
			fov = 179.f;

		m_fov = fov;
	}

	void camera_perspective::update_projection()
	{
		m_projection = glm::perspective(glm::radians(get_fov()), static_cast<float>(get_frame_dimensions().x) / static_cast<float>(get_frame_dimensions().y), get_planes().x, get_planes().y);
	}

}