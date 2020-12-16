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
		fov_ = std::abs(std::fmodf(fov, 180.f));
	}

	void CCameraPerspective::updateProjection() const
	{
		projection_ = glm::perspective(glm::radians(getFOV()), static_cast<float>(getFrameDimensions().x) / static_cast<float>(getFrameDimensions().y), getPlanes().x, getPlanes().y);
	}

}