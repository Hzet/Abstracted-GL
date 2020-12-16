#pragma once 

#include <glm/glm.hpp>
#include "camera-base.hpp"

namespace agl
{
	class CCameraPerspective
		: public ICamera
	{
	public:
		using ICamera::ICamera;
		
		float getFOV() const;
		void setFOV(float fov);

	protected:
		virtual void updateProjection() const override;

	private:
		float fov_;
	};
}