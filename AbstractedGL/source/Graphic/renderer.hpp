#pragma once 

#include "window-base.hpp"
#include "shader-program.hpp"
#include "vertex-array.hpp"

namespace agl
{
	/// <summary>
	/// A basic renderer class that is capable of rendering the vertex arrays and stores the relevant shaders.
	/// </summary>
	class CRenderer
	{
	public:
		/// <summary>
		/// Draw 'vArray' as 'drawType'.
		/// </summary>
		/// <param name="vArray">Vertex array</param>
		/// <param name="drawType">OpenGL draw type enum</param>
		void draw(const CVertexArray &vArray, std::uint64_t drawType) const;
	};
}