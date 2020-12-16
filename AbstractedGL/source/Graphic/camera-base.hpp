#pragma once

#include <glm/glm.hpp>
#include "transform.hpp"

namespace agl
{
	struct SDirection
	{
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
	};

	class ICamera
	{
	public:
		static const SDirection WorldDirection;

		ICamera();
		ICamera(ICamera&&) = default;
		ICamera(const ICamera&) = default;
		virtual ~ICamera() = default;

		ICamera& operator=(ICamera&&) = default;
		ICamera& operator=(const ICamera&) = default;

		const glm::uvec2& getFrameDimensions() const;
		void setFrameDimensions(const glm::uvec2 &frame);

		const glm::vec2& getPlanes() const;
		void setPlanes(const glm::vec2 &planes);
		
		const glm::vec3& getScale() const;
		void setScale(const glm::vec3 &scale);

		const glm::vec3& getPosition() const;
		void setPosition(const glm::vec3 &position);

		const glm::vec3& getRotation() const;
		void setRotation(const glm::vec3 &rotation);

		void scale(const glm::vec3 &scale);
		void move(const glm::vec3 &offset);
		void rotate(const glm::vec3 &angle);

		const CTransform& getView() const;
		const CTransform& getProjection() const;
	
		const SDirection& getDirection() const;

	protected:
		void updateView() const;
		virtual void updateProjection() const = 0;

		mutable CTransform projection_;

	private:
		glm::vec2 planes_; // near / far

		glm::uvec2 frameDimensions_;

		glm::vec3 scale_;
		glm::vec3 position_;
		glm::vec3 rotation_;

		mutable bool viewUpdate_;
		mutable bool projUpdate_;
		mutable CTransform view_;
		mutable SDirection direction_;
	};
}