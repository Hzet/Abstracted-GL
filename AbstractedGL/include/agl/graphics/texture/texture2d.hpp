#pragma once
#include <glm/glm.hpp>
#include "agl/graphics/texture/texture-base.hpp"
#include "agl/graphics/texture/texture-uid.hpp"

namespace agl
{
	/// <summary>
	/// 2D texture
	/// </summary>
	class texture_2d
		: public texture_base
	{
	public:
		using texture_base::texture_base;

		/// <summary>
		/// Set dimensions to 0.
		/// </summary>
		texture_2d();

		/// <summary>
		/// Loads the texture from a file.
		/// </summary>
		/// <param name="filename">The filepath</param>
		/// <returns>
		/// True - texture loaded successfully
		/// False - failed to load the texture
		/// </returns>
		bool load_from_file(const std::string &filepath);
	};
}