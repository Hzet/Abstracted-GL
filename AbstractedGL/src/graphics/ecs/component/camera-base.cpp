#include "agl/graphics/ecs/component/camera-base.hpp"

#include <glm/ext.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace agl
{
	const direction camera_base::s_world_direction = { glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 0.f, 0.f) };

	camera_base::camera_base()
		: m_planes{ 0.1f, 100.f }
		, m_look_at{ 0.f, 0.f, 0.f }
		, m_view_update{ true }
		, m_projection_update{ true }
		, m_view{ glm::mat4{ 1.f } }
		, m_projection{ glm::mat4{ 1.f } }
	{
	}

	const glm::vec2& camera_base::get_resolution() const
	{
		return m_resolution;
	}

	void camera_base::set_resolution(const glm::vec2 &frame)
	{
		m_view_update = true;

		m_resolution = frame;
	}

	const glm::vec2& camera_base::get_planes() const
	{
		return m_planes;
	}

	void camera_base::set_planes(const glm::vec2 &planes)
	{
		m_view_update = true;

		m_planes = planes;
	}

	const transform& camera_base::get_view() const
	{
		return m_view;
	}

	void camera_base::look_at(const glm::vec3 &target)
	{
		m_look_at_update = true;
		m_look_at = target;
	}

	bool camera_base::needs_update() const
	{
		return m_view_update || m_look_at_update;
	}

	void camera_base::update(transformable& transform, direction& dir)
	{
		if (m_look_at_update)
		{
			if (transform.get_origin() + transform.get_position() != m_look_at)
			{

				dir.forward = glm::normalize(m_look_at - transform.get_origin() - transform.get_position());
				dir.right = glm::normalize(glm::cross(dir.forward, s_world_direction.up));
				dir.up = glm::normalize(glm::cross(dir.right, dir.forward));

				auto rotation = glm::vec3{ 0.f };

				rotation.x = glm::degrees(glm::atan(dir.forward.z, dir.forward.x));
				rotation.y = glm::degrees(glm::atan(dir.forward.y, glm::length(glm::vec2(dir.forward.x, dir.forward.z))));

				transform.set_rotation(rotation);
			}

			m_look_at_update = false;
		}

		if (transform.get_rotation().y > 89.f)
			transform.set_rotation(glm::vec3{ transform.get_rotation().x, 89.f, transform.get_rotation().z });
		else if (transform.get_rotation().y < -89.f)
			transform.set_rotation(glm::vec3{ transform.get_rotation().x, -89.f, transform.get_rotation().z });

		dir.forward.x = glm::cos(glm::radians(transform.get_rotation().x)) * glm::cos(glm::radians(transform.get_rotation().y));
		dir.forward.y = glm::sin(glm::radians(transform.get_rotation().y));
		dir.forward.z = glm::sin(glm::radians(transform.get_rotation().x)) * glm::cos(glm::radians(transform.get_rotation().y));

		dir.forward = glm::normalize(dir.forward);
		dir.right = glm::normalize(glm::cross(dir.forward, s_world_direction.up));
		dir.up = glm::normalize(glm::cross(dir.right, dir.forward));

		m_view = glm::lookAt(transform.get_origin() + transform.get_position(), transform.get_origin() + transform.get_position() + dir.forward, dir.up);
		m_view.scale(transform.get_scale());

		m_view_update = false;
		m_projection_update = true;
	}
}