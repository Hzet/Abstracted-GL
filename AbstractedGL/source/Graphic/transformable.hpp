#pragma once

#include "transform.hpp"

namespace agl
{
	class CTransformable
	{
	public:
		CTransformable();
		CTransformable(CTransformable&&) = default;
		CTransformable(const CTransformable&) = default;
		virtual ~CTransformable() = default;

		const glm::vec3& getScale() const;
		void setScale(const glm::vec3 &scale);

		const glm::vec3& getOrigin() const;
		void setOrigin(const glm::vec3 &origin);

		const glm::vec3& getPosition() const;
		void setPosition(const glm::vec3 &position);

		const glm::vec3& getRotation() const;
		void setRotation(const glm::vec3 &rotation);

		void move(const glm::vec3 &offset);
		void scale(const glm::vec3 &ratio);
		void rotate(const glm::vec3 &angle);

		const CTransform& getTransform() const;

	private:
		glm::vec3 scale_;
		glm::vec3 origin_;
		glm::vec3 position_;
		glm::vec3 rotation_;
		CTransform transform_;
	};
}