#pragma once
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-base.hpp"

namespace agl
{
	class inverse_transform_uniform
		: uniform_base
	{
	public:
		inverse_transform_uniform();

		std::unique_ptr<uniform_member<glm::mat4>> inverse_transform;
	};
}
