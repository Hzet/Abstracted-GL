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

		/// <summary>
		/// Add to the collection and take the ownership of the 'shader'.
		/// The 'shader' must be first successfully linked.
		/// </summary>
		/// <param name="name">Shader unique identifier</param>
		/// <param name="shader">Shader program to be moved</param>
		void addShader(std::uint32_t name, CShader &&shader);

		/// <summary>
		/// Get the const reference to the specified shader.
		/// </summary>
		/// <param name="name">Shader's unique identifier</param>
		/// <returns>
		/// The shader
		/// </returns>
		const CShader& getShader(std::uint32_t name) const;

		/// <summary>
		/// Get the shader that has been set as active.
		/// </summary>
		/// <returns>
		/// The active shader
		/// </returns>
		const CShader& getActiveShader() const;

		/// <summary>
		/// Set the specified shader as active.
		/// </summary>
		/// <param name="name">Shader's unique identifier</param>
		void setActiveShader(std::uint32_t name);

	private:
		std::uint32_t active_;
		std::unordered_map<std::uint32_t, CShader> shaders_;
	};
}