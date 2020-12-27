#pragma once

#include "camera-base.hpp"

namespace agl
{
	/// <summary>
	/// Orthographic camera
	/// </summary>
	class CCameraOrthographic
		: public ICamera
	{
	protected:
		/// <summary>
		/// Update 'projection_' matrix.
		/// </summary>
		virtual void updateProjection() const override;
	};
}