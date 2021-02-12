#pragma once
#include <unordered_map>

#include "shader-program.hpp"
#include "shader-uid.hpp"

namespace agl
{
	/// <summary>
	/// A library that stores shaders for different objects to use.
	/// One can define a static variable atop of the object's .cpp file, attach required shaders, link it and then pass it to this class' constructor.
	/// </summary>
	class CShaderManager
	{
	public:
		/// <summary>
		/// Add 'shader' to the 'Shaders_' library.
		/// The 'shader' must be a ready to use (successfully linked) shader, it will not work otherwise.
		/// </summary>
		/// <param name="key">the unique identifier of the 'shader'</param>
		/// <param name="shader">ready to use shader object</param>
		CShaderManager(const CShaderUID &uid, CShader &&shader);

		/// <summary>
		/// Return the shader with given 'key'.
		/// </summary>
		/// <param name="key">the unique identifier of the 'shader'</param>
		/// <returns>the shader</returns>
		static const CShader& GetShader(const CShaderUID &uid);

		/// <summary>
		/// Adds the 'shader' with unique identifier 'key'.
		/// The 'shader' must be a ready to use (successfully linked) shader, it will not work otherwise.
		/// </summary>
		/// <param name="key">the unique identifier of the 'shader'</param>
		/// <param name="shader">ready to use shader object</param>
		static void AddShader(const CShaderUID &uid, CShader &&shader);

	private:
		friend class CWindowBase;

		/// <summary>
		/// Iterates through every shader added and tries to link it if the shader is not yet linked.
		/// </summary>
		/// <returns>
		/// True - all shaders linked
		/// False - at least one shader could not be linked
		/// </returns>
		static bool LinkAllShaders();

		static std::unordered_map<CShaderUID, CShader>& GetShaders();
	};
}