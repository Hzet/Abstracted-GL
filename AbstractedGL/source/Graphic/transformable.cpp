#include "transformable.hpp"

namespace agl
{

	CTransformable::CTransformable()
		: scale_(1.f),
		origin_(0.f),
		position_(0.f),
		rotation_(0.f)
	{
	}

	const glm::vec3& CTransformable::getScale() const
	{
		return scale_;
	}

	void CTransformable::setScale(const glm::vec3 &scale)
	{
		transform_.scale(scale / scale_);
		scale_ = scale;
	}

	const glm::vec3& CTransformable::getOrigin() const
	{
		return origin_;
	}

	void CTransformable::setOrigin(const glm::vec3 &origin)
	{
		transform_.translate(origin - origin_);
		origin_ = origin;
	}

	const glm::vec3& CTransformable::getPosition() const
	{
		return position_;
	}

	void CTransformable::setPosition(const glm::vec3 &position)
	{
		transform_.translate(origin_ + position - position_);
		position_ = position;
	}

	const glm::vec3& CTransformable::getRotation() const
	{
		return rotation_;
	}

	void CTransformable::setRotation(const glm::vec3 &rotation)
	{
		transform_.rotate(rotation - rotation_);
		rotation_ = rotation;
	}

	void CTransformable::move(const glm::vec3 &offset)
	{
		setPosition(position_ + offset);
	}

	void CTransformable::scale(const glm::vec3 &ratio)
	{
		setScale(scale_ * ratio);
	}

	void CTransformable::rotate(const glm::vec3 &angle)
	{
		setRotation(rotation_ + angle);
	}

	const agl::CTransform& CTransformable::getTransform() const
	{
		return transform_;
	}
}