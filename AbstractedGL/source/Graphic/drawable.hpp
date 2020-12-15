#pragma once 

#include "vertex-array.hpp"

namespace agl
{
	class  CRenderer;

	struct IDrawable
	{
		virtual void draw(const CRenderer &renderer) const = 0;
	};

}