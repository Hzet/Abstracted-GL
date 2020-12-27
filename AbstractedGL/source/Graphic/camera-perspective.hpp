#pragma once 

#include <glm/glm.hpp>
#include "camera-base.hpp"

namespace agl
{
	/// <summary>
	/// Perspective camera.
	/// </summary>
	class CCameraPerspective
		: public ICamera
	{
	public:
		using ICamera::ICamera;
		
		/// <summary>
		/// Get camera's 'fov_'.
		/// </summary>
		/// <returns>
		/// The field of view
		/// </returns>
		float getFOV() const;

		/// <summary>
		/// Set camera's 'fov_'.
		/// </summary>
		/// <param name="fov">The field of view</param>
		void setFOV(float fov);

	protected:
		/// <summary>
		/// Recalculate the projection matrix.
		/// </summary>
		virtual void updateProjection() const override;

	private:
		float fov_;
	};
}