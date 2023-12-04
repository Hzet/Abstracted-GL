#pragma once 
#include <glm/glm.hpp>

#include "agl/graphics/ecs/component/camera-base.hpp"

namespace agl
{
	/// <summary>
	/// Perspective camera.
	/// </summary>
	class camera_perspective
		: public camera_base
	{
	public:
		using camera_base::camera_base;
		
		camera_perspective();

		/// <summary>
		/// Get camera's 'm_fov'.
		/// </summary>
		/// <returns>
		/// The field of view
		/// </returns>
		float get_fov() const;

		/// <summary>
		/// Set camera's 'm_fov'.
		/// </summary>
		/// <param name="fov">The field of view</param>
		void set_fov(float fov);

		/// <summary>
		/// Recalculate the projection matrix.
		/// </summary>
		const transform& calc_projection();

	private:
		float m_fov;
	};
}