#pragma once
#include "agl/utility/ecs/registry.hpp"
#include "agl/graphics/ecs/system-group.hpp"

namespace agl
{
	const bool g_default_system_order = registry::order<simulation_group, render_group, window_group>();
}