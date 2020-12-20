#include "transform.hpp"

#include <glm/ext.hpp>

namespace agl
{
	CTransform::CTransform()
		: matrix_(1.f)
	{
	}

	CTransform::CTransform(const glm::mat4 &matrix)
		: matrix_(matrix)
	{
	}

	void CTransform::scale(const glm::vec3 &scale)
	{
		matrix_ = glm::scale(matrix_, scale);
	}

	void CTransform::rotate(const glm::vec3 &angle)
	{
		matrix_ = glm::rotate(matrix_, glm::radians(angle.x), { 1.f, 0.f, 0.f });
		matrix_ = glm::rotate(matrix_, glm::radians(angle.y), { 0.f, 1.f, 0.f });
		matrix_ = glm::rotate(matrix_, glm::radians(angle.z), { 0.f, 0.f, 1.f });
	}

	void CTransform::translate(const glm::vec3 &offset)
	{
		matrix_ = glm::translate(matrix_, offset);
	}

	CTransform CTransform::getInverse() const
	{
		return glm::inverse(matrix_);
	}

	CTransform& CTransform::operator*=(const CTransform &other)
	{
		matrix_ = matrix_ * other.matrix_;
		return *this;
	}

	CTransform CTransform::operator*(const CTransform &other) const
	{
		return matrix_ * other.matrix_;
	}

	CTransform::operator const glm::mat4&() const
	{
		return matrix_;
	}

/*
	CTransform::operator glm::mat4&()
	{
		return matrix_;
	}*/
}