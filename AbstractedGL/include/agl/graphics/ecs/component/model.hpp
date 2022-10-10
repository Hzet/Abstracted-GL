#pragma once
#include "graphics/ecs/component/mesh.hpp"

namespace agl
{
	class model
	{
	public:
		std::vector<mesh> meshes;
		uniform_array uniforms;
	};
}

