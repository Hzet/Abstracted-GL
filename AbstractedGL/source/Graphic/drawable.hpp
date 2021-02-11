#pragma once 

#include "vertex-array.hpp"

namespace agl
{
	class CRenderer;

	/// <summary>
	/// Interface for drawable objects.
	/// </summary>
	struct IDrawable
	{
		/// <summary>
		/// Draw the object using 'renderer'.
		/// </summary>
		/// <param name="renderer">The renderer</param>
		virtual void draw(const CRenderer &renderer) const = 0;
	};

}