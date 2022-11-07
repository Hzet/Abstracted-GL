#pragma once
#include <string>

#include "agl/graphics/ecs/component/gui/gui-base.hpp"
#include "agl/graphics/ecs/component/rectangle.hpp"

namespace agl
{
	class button
		: public gui_base
		, public rectangle
	{
	private:
		std::string m_text;
	};
}