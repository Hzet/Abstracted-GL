#include "transformable.hpp"
#include <iostream>
#include <glm/ext.hpp>

namespace agl
{

	CTransformable::CTransformable()
		: requireUpdate_(false),
		scale_(1.f),
		origin_(0.f),
		position_(0.f),
		rotation_(0.f),
		parent_(nullptr)
	{
	}


	CTransformable::CTransformable(CTransformable &&other)
		: requireUpdate_(false),
		scale_(std::move(other.scale_)),
		origin_(std::move(other.origin_)),
		position_(std::move(other.position_)),
		rotation_(std::move(other.rotation_)),
		parent_(nullptr)
	{
	}


	CTransformable::CTransformable(const CTransformable &other)
		: requireUpdate_(false),
		scale_(other.scale_),
		origin_(other.origin_),
		position_(other.position_),
		rotation_(other.rotation_),
		parent_(nullptr)
	{
	}

	const glm::vec3& CTransformable::getScale() const
	{
		requireUpdate_ = true;

		return scale_;
	}

	void CTransformable::setScale(const glm::vec3 &scale)
	{
		requireUpdate_ = true;

		scale_ = scale;
	}

	const glm::vec3& CTransformable::getOrigin() const
	{
		return origin_;
	}

	void CTransformable::setOrigin(const glm::vec3 &origin)
	{
		requireUpdate_ = true;

		origin_ = origin;
	}

	const glm::vec3& CTransformable::getPosition() const
	{
		return position_;
	}

	void CTransformable::setPosition(const glm::vec3 &position)
	{
		requireUpdate_ = true;

		position_ = position;
	}

	const glm::vec3& CTransformable::getRotation() const
	{
		return rotation_;
	}

	void CTransformable::setRotation(const glm::vec3 &rotation)
	{
		requireUpdate_ = true;

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

	void CTransformable::setTransform(const CTransform &transform)
	{
		requireUpdate_ = true;

		transform_ = transform;
	}

	const CTransform& CTransformable::getTransform() const
	{
		update();

		return transform_;
	}

	const CTransform& CTransformable::getInverseTransform() const
	{
		update();
	
		return inverseTransform_;
	}

	bool CTransformable::hasParent() const
	{
		return parent_ != nullptr;
	}

	const CTransformable& CTransformable::getParent() const
	{
		return *parent_;
	}

	void CTransformable::setParent(const CTransformable &parent)
	{
		parent_ = &parent;
	}

	void CTransformable::update() const
	{
		if (!requireUpdate_ && !hasParent())
			return;
		else if (hasParent())
			if (!getParent().requireUpdate_)
				return;
		
		transform_ = CTransform();

		transform_.translate(origin_ + position_);
		transform_.scale(scale_);
		transform_.rotate(rotation_);

		if (hasParent())
			transform_ = getParent().getTransform() * transform_;

		inverseTransform_ = glm::inverse(static_cast<glm::mat4>(transform_));

		requireUpdate_ = false;
	}

}