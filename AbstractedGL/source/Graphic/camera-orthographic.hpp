#pragma once

#include "camera-base.hpp"

namespace agl
{
	class CCameraOrthographic
		: public ICamera
	{
	protected:
		virtual void updateProjection() const override;
	};
}