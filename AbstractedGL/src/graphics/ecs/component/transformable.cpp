#include "graphics/ecs/component/transformable.hpp"

#include <glm/ext.hpp>

namespace agl
{

	transformable::transformable()
		: m_require_update(false),
		m_scale(1.f),
		m_origin(0.f),
		m_position(0.f),
		m_rotation(0.f),
		m_parent(nullptr)
	{
	}


	transformable::transformable(transformable &&other)
		: m_require_update(false),
		m_scale(std::move(other.m_scale)),
		m_origin(std::move(other.m_origin)),
		m_position(std::move(other.m_position)),
		m_rotation(std::move(other.m_rotation)),
		m_parent(nullptr)
	{
	}


	transformable::transformable(const transformable &other)
		: m_require_update(false),
		m_scale(other.m_scale),
		m_origin(other.m_origin),
		m_position(other.m_position),
		m_rotation(other.m_rotation),
		m_parent(nullptr)
	{
	}

	const glm::vec3& transformable::get_scale() const
	{
		m_require_update = true;

		return m_scale;
	}

	void transformable::set_scale(const glm::vec3 &scale)
	{
		m_require_update = true;

		m_scale = scale;
	}

	const glm::vec3& transformable::getOrigin() const
	{
		return m_origin;
	}

	void transformable::setOrigin(const glm::vec3 &origin)
	{
		m_require_update = true;

		m_origin = origin;
	}

	const glm::vec3& transformable::get_position() const
	{
		return m_position;
	}

	void transformable::set_position(const glm::vec3 &position)
	{
		m_require_update = true;

		m_position = position;
	}

	const glm::vec3& transformable::get_rotation() const
	{
		return m_rotation;
	}

	void transformable::set_rotation(const glm::vec3 &rotation)
	{
		m_require_update = true;

		m_rotation = rotation;
	}

	void transformable::move(const glm::vec3 &offset)
	{
		set_position(m_position + offset);
	}

	void transformable::scale(const glm::vec3 &ratio)
	{
		set_scale(m_scale * ratio);
	}

	void transformable::rotate(const glm::vec3 &angle)
	{
		set_rotation(m_rotation + angle);
	}

	void transformable::set_transform(const transform &transform)
	{
		m_require_update = true;

		m_transform = transform;
	}

	const transform& transformable::get_transform() const
	{
		update();

		return m_transform;
	}

	const transform& transformable::get_inverse_transform() const
	{
		update();

		return m_inverse_transform;
	}

	bool transformable::has_parent() const
	{
		return m_parent != nullptr;
	}

	const transformable& transformable::get_parent() const
	{
		return *m_parent;
	}

	void transformable::set_parent(const transformable &parent)
	{
		m_parent = &parent;
	}

	void transformable::update() const
	{
		if (!m_require_update && !has_parent())
			return;
		else if (has_parent())
			if (!get_parent().m_require_update)
				return;

		m_transform = transform();

		m_transform.translate(m_origin + m_position);
		m_transform.scale(m_scale);
		m_transform.rotate(m_rotation);

		if (has_parent())
			m_transform = get_parent().get_transform() * m_transform;

		m_inverse_transform = glm::inverse(static_cast<glm::mat4>(m_transform));

		m_require_update = false;
	}
}