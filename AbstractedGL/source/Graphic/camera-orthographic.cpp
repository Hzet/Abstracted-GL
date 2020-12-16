#include "camera-orthographic.hpp"

#include <glm/ext.hpp>

namespace agl
{

	void CCameraOrthographic::updateProjection() const
	{
		projection_ = glm::ortho(0.f, static_cast<float>(getFrameDimensions().x), 0.f, static_cast<float>(getFrameDimensions().y), getPlanes().x, getPlanes().y);
	}

}