#include "graphics/ecs/component/transform.hpp"

#include <glm/ext.hpp>

namespace agl
{
	transform::transform()
		: m_matrix(1.f)
	{
	}

	transform::transform(const glm::mat4 &matrix)
		: m_matrix(matrix)
	{
	}

	void transform::scale(const glm::vec3 &scale)
	{
		m_matrix = glm::scale(m_matrix, scale);
	}

	void transform::rotate(const glm::vec3 &angle)
	{
		m_matrix = glm::rotate(m_matrix, glm::radians(angle.x), { 1.f, 0.f, 0.f });
		m_matrix = glm::rotate(m_matrix, glm::radians(angle.y), { 0.f, 1.f, 0.f });
		m_matrix = glm::rotate(m_matrix, glm::radians(angle.z), { 0.f, 0.f, 1.f });
	}

	void transform::translate(const glm::vec3 &offset)
	{
		m_matrix = glm::translate(m_matrix, offset);
	}

	transform& transform::operator*=(const transform &other)
	{
		m_matrix = m_matrix * other.m_matrix;
		return *this;
	}

	transform transform::operator*(const transform &other) const
	{
		return m_matrix * other.m_matrix;
	}

	transform::operator const glm::mat4&() const
	{
		return m_matrix;
	}

}