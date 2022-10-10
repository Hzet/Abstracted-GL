#include "graphics/ecs/component/camera-base.hpp"

#include <glm/ext.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace agl
{
	const direction_matrix camera_base::s_world_direction = { glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 0.f, 0.f) };

	camera_base::camera_base()
		: m_planes(0.1f, 100.f)
		, m_position(0.f)
		, m_rotation(0.f)
		, m_scale(glm::vec3{1.f})
		, m_view_update(true)
		, m_proj_update(true)
		, m_view(glm::mat4{ 1.f })
		, m_direction(s_world_direction)
	{
	}

	const glm::uvec2& camera_base::get_frame_dimensions() const
	{
		return m_frame_dimensions;
	}

	void camera_base::set_frame_dimensions(const glm::uvec2 &frame)
	{
		m_proj_update = true;

		m_frame_dimensions = frame;
	}

	const glm::vec2& camera_base::get_planes() const
	{
		return m_planes;
	}

	void camera_base::set_planes(const glm::vec2 &planes)
	{
		m_proj_update = true;

		m_planes = planes;
	}

	const glm::vec3& camera_base::get_scale() const
	{
		return m_scale;
	}

	void camera_base::set_scale(const glm::vec3 &scale)
	{
		m_view_update = true;

		m_scale = scale;
	}

	const glm::vec3& camera_base::get_position() const
	{
		return m_position;
	}

	void camera_base::set_position(const glm::vec3 &position)
	{
		m_view_update = true;

		m_position = position;
	}

	const glm::vec3& camera_base::get_rotation() const
	{
		return m_rotation;
	}

	void camera_base::set_rotation(const glm::vec3 &rotation)
	{
		m_view_update = true;

		if (m_rotation.y < -89.f)
			m_rotation.y = -89.f;
		else if (m_rotation.y > 89.f)
			m_rotation.y = 89.f;
		else
			m_rotation.y = rotation.y;

		m_rotation.x = std::fmodf(rotation.x, 360.f);
		m_rotation.z = std::fmodf(rotation.z, 360.f);
	}

	void camera_base::scale(const glm::vec3 &scale)
	{
		set_scale(m_scale * scale);
	}

	void camera_base::move(const glm::vec3 &offset)
	{
		set_position(get_position() + offset);
	}

	void camera_base::rotate(const glm::vec3 &angle)
	{
		set_rotation(get_rotation() + angle);
	}

	const transform& camera_base::get_view() const
	{
		if (m_view_update)
		{
			update_view();

			m_view_update = false;
		}

		return m_view;
	}

	const transform& camera_base::get_projection() const
	{
		if (m_proj_update)
		{
			this->update_projection();

			m_proj_update = false;
		}

		return m_projection;
	}

	const direction_matrix& camera_base::get_direction() const
	{
		return m_direction;
	}

	void camera_base::look_at(const glm::vec3 &position)
	{
		if (get_position() == position)
			return;

		m_view_update = true;

		m_direction.forward = glm::normalize(position - m_position);
		m_direction.right = glm::normalize(glm::cross(m_direction.forward, s_world_direction.up));
		m_direction.up = glm::normalize(glm::cross(m_direction.right, m_direction.forward));

		m_rotation.x = glm::degrees(glm::atan(m_direction.forward.z, m_direction.forward.x));
		m_rotation.y = glm::degrees(glm::atan(m_direction.forward.y, glm::length(glm::vec2(m_direction.forward.x, m_direction.forward.z))));
	}

	void camera_base::update_view() const
	{
		m_direction.forward.x = glm::cos(glm::radians(m_rotation.x)) * glm::cos(glm::radians(m_rotation.y));
		m_direction.forward.y = glm::sin(glm::radians(m_rotation.y));
		m_direction.forward.z = glm::sin(glm::radians(m_rotation.x)) * glm::cos(glm::radians(m_rotation.y));

		m_direction.forward = glm::normalize(m_direction.forward);
		m_direction.right = glm::normalize(glm::cross(m_direction.forward, s_world_direction.up));
		m_direction.up = glm::normalize(glm::cross(m_direction.right, m_direction.forward));

		m_view = glm::lookAt(m_position, m_position + m_direction.forward, m_direction.up);
		m_view.scale(m_scale);
	}
}