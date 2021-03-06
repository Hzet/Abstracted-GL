#include "camera-base.hpp"
#include <glm/ext.hpp>
#include <glm/gtx/vector_angle.hpp>





#include <iostream>
namespace agl
{
	const SDirection ICamera::WorldDirection = { glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 0.f, 0.f) };

	ICamera::ICamera()
		: planes_(0.f, 100.f),
		position_(0.f),
		rotation_(0.f),
		scale_(glm::vec3(1.f)),
		viewUpdate_(false),
		projUpdate_(false),
		direction_(WorldDirection)
	{
	}

	const glm::uvec2& ICamera::getFrameDimensions() const
	{
		return frameDimensions_;
	}

	void ICamera::setFrameDimensions(const glm::uvec2 &frame)
	{
		projUpdate_ = true;

		frameDimensions_ = frame;
	}

	const glm::vec2& ICamera::getPlanes() const
	{
		return planes_;
	}

	void ICamera::setPlanes(const glm::vec2 &planes)
	{
		projUpdate_ = true;

		planes_ = planes;
	}

	const glm::vec3& ICamera::getScale() const
	{
		return scale_;
	}

	void ICamera::setScale(const glm::vec3 &scale)
	{
		viewUpdate_ = true;

		scale_ = scale;
	}

	const glm::vec3& ICamera::getPosition() const
	{
		return position_;
	}

	void ICamera::setPosition(const glm::vec3 &position)
	{
		viewUpdate_ = true;

		position_ = position;
	}

	const glm::vec3& ICamera::getRotation() const
	{
		return rotation_;
	}

	void ICamera::setRotation(const glm::vec3 &rotation)
	{
		viewUpdate_ = true;

		if (rotation_.y < -89.f)
			rotation_.y = -89.f;
		else if (rotation_.y > 89.f)
			rotation_.y = 89.f;
		else
			rotation_.y = rotation.y;

		rotation_.x = std::fmodf(rotation.x, 360.f);
		rotation_.z = std::fmodf(rotation.z, 360.f);
	}

	void ICamera::scale(const glm::vec3 &scale)
	{
		setScale(scale_ * scale);
	}

	void ICamera::move(const glm::vec3 &offset)
	{
		setPosition(getPosition() + offset);
	}

	void ICamera::rotate(const glm::vec3 &angle)
	{
		setRotation(getRotation() + angle);
	}

	const CTransform& ICamera::getView() const
	{
		if (viewUpdate_)
		{
			updateView();

			viewUpdate_ = false;
		}

		return view_;
	}

	const CTransform& ICamera::getProjection() const
	{
		if (projUpdate_)
		{
			this->updateProjection();

			projUpdate_ = false;
		}

		return projection_;
	}

	const SDirection& ICamera::getDirection() const
	{
		return direction_;
	}

	void ICamera::lookAt(const glm::vec3 &position)
	{
		viewUpdate_ = true;

		direction_.forward = glm::normalize(position - position_);
		direction_.right = glm::normalize(glm::cross(direction_.forward, WorldDirection.up));
		direction_.up = glm::normalize(glm::cross(direction_.right, direction_.forward));

		rotation_.x = glm::degrees(glm::atan(direction_.forward.z, direction_.forward.x));
		rotation_.y = glm::degrees(glm::atan(direction_.forward.y, glm::length(glm::vec2(direction_.forward.x, direction_.forward.z))));
	}

	void ICamera::updateView() const
	{
		direction_.forward.x = glm::cos(glm::radians(rotation_.x)) * glm::cos(glm::radians(rotation_.y));
		direction_.forward.y = glm::sin(glm::radians(rotation_.y));
		direction_.forward.z = glm::sin(glm::radians(rotation_.x)) * glm::cos(glm::radians(rotation_.y));

		direction_.forward = glm::normalize(direction_.forward);
		direction_.right = glm::normalize(glm::cross(direction_.forward, WorldDirection.up));
		direction_.up = glm::normalize(glm::cross(direction_.right, direction_.forward));

		view_ = glm::lookAt(position_, position_ + direction_.forward, direction_.up);
		view_.scale(scale_);
	}
}