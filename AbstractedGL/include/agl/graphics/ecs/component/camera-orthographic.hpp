#pragma once
#include "agl/graphics/ecs/component/camera-base.hpp"

namespace agl
{
	/// <summary>
	/// Orthographic camera
	/// </summary>
	class camera_orthographic
		: public camera_base
	{
	public:
		using camera_base::camera_base;

	protected:
		/// <summary>
		/// Update 'm_projection' matrix.
		/// </summary>
		virtual void update_projection() override;
	};
}