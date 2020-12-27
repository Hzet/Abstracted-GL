#pragma once

#include <glm/glm.hpp>
#include "transform.hpp"

namespace agl
{
	/// <summary>
	/// Aggregation struct to store direction vectors.
	/// </summary>
	struct SDirection
	{
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
	};

	/// <summary>
	/// A base class for the cameras.
	/// Virtual updateProjection method will be called from getProjection method when the matrix will require update.
	/// </summary>
	class ICamera
	{
	public:
		static const SDirection WorldDirection;

		/// <summary>
		/// Set transform properties to 0 or 1 for scale and planes to {0, 100}.
		/// </summary>
		ICamera();

		ICamera(ICamera&&) = default;
		ICamera(const ICamera&) = default;
		virtual ~ICamera() = default;

		ICamera& operator=(ICamera&&) = default;
		ICamera& operator=(const ICamera&) = default;

		/// <summary>
		/// Get the dimension of the rendering screen.
		/// </summary>
		/// <returns>
		/// The dimensions
		/// </returns>
		const glm::uvec2& getFrameDimensions() const;

		/// <summary>
		/// Set the dimension of the rendering screen.
		/// </summary>
		/// <param name="frame">The dimensions</returns>
		void setFrameDimensions(const glm::uvec2 &frame);

		/// <summary>
		/// Get the camera's near and far 'planes'.
		/// </summary>
		/// <returns>
		/// The planes 
		/// </returns>
		const glm::vec2& getPlanes() const;

		/// <summary>
		/// Set the camera's near and far 'planes'.
		/// </summary>
		/// <param name="planes">The planes</param>
		void setPlanes(const glm::vec2 &planes);
		
		/// <summary>
		/// Get the view's 'scale'.
		/// </summary>
		/// <returns>
		/// The scale
		/// </returns>
		const glm::vec3& getScale() const;

		/// <summary>
		/// Set the view's 'scale'.
		/// </summary>
		/// <param name="scale">The scale</param>
		void setScale(const glm::vec3 &scale);

		/// <summary>
		/// Get the 'position' of the camera.
		/// </summary>
		/// <returns>
		/// The position
		/// </returns>
		const glm::vec3& getPosition() const;

		/// <summary>
		/// Set the position of the camera.
		/// </summary>
		/// <param name="position">The position</param>
		void setPosition(const glm::vec3 &position);

		/// <summary>
		/// Get the 'rotation' of the camera.
		/// </summary>
		/// <returns>
		/// The roatation
		/// </returns>
		const glm::vec3& getRotation() const;

		/// <summary>
		/// Set the 'rotation' of the camera.
		/// </summary>
		/// <param name="rotation">The rotation</param>
		void setRotation(const glm::vec3 &rotation);

		/// <summary>
		/// Scale the object by a 'scale'.
		/// </summary>
		/// <param name="scale"></param>
		void scale(const glm::vec3 &scale);

		/// <summary>
		/// Move the camera by an 'offset'.
		/// </summary>
		/// <param name="offset">The offset</param>
		void move(const glm::vec3 &offset);

		/// <summary>
		/// Rotate the camera by an 'angle'.
		/// </summary>
		/// <param name="angle">The angle</param>
		void rotate(const glm::vec3 &angle);

		/// <summary>
		/// Get the 'view_' matrix.
		/// </summary>
		/// <returns>
		/// The view matrix
		/// </returns>
		const CTransform& getView() const;

		/// <summary>
		/// Get the 'projection_' matrix.
		/// </summary>
		/// <returns>
		/// The projection matrix
		/// </returns>
		const CTransform& getProjection() const;
	
		/// <summary>
		/// Get the directions of the camera.
		/// </summary>
		/// <returns>
		/// The direction
		/// </returns>
		const SDirection& getDirection() const;

	protected:
		/// <summary>
		/// Recalculate the 'view_' matrix.
		/// </summary>
		void updateView() const;

		/// <summary>
		/// Recalculate the 'projection_' matrix.
		/// </summary>
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