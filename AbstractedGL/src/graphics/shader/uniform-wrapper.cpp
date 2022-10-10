#include "graphics/shader/uniform-wrapper.hpp"

namespace agl
{
	const uniform_base& uniform_wrapper_base::get_uniform() const
	{
		return *uniform_;
	}
}

