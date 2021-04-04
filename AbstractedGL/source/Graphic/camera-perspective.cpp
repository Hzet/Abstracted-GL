#include "camera-perspective.hpp"
#include <glm/ext.hpp>

namespace agl
{
	float CCameraPerspective::getFOV() const
	{
		return fov_;
	}

	void CCameraPerspective::setFOV(float fov)
	{
		projUpdate_ = true;
	
		if (fov < 0.f)
			fov = 0.f;
		else if (fov >= 179.f)
			fov = 179.f;

		fov_ = fov;
	}

	void CCameraPerspective::updateProjection() const
	{
		projection_ = glm::perspective(glm::radians(getFOV()), static_cast<float>(getFrameDimensions().x) / static_cast<float>(getFrameDimensions().y), getPlanes().x, getPlanes().y);
	}

}