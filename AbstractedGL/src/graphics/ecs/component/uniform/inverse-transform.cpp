#include "graphics/ecs/component/uniform/inverse-transform.hpp"

namespace agl
{
	inverse_transform_uniform::inverse_transform_uniform()
	{
		inverse_transform = create_member<glm::mat4>("inverse_transform", [](auto& e) { return e.get_attachment<transformable>().get_inverse_transform(); });
	}
}

