#pragma once
#include <glm/glm.hpp>
#include "graphics/texture/texture-base.hpp"
#include "graphics/texture/texture-uid.hpp"

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
		/// Get dimensions
		/// </summary>
		/// <returns>
		/// The dimensions
		/// </returns>
		const glm::uvec2& get_dimensions() const;

		/// <summary>
		/// Loads the texture from a file.
		/// </summary>
		/// <param name="filename">The filepath</param>
		/// <returns>
		/// True - texture loaded successfully
		/// False - failed to load the texture
		/// </returns>
		bool load_from_file(const std::string &filename);

		virtual texture_type get_target() const override;

	private:
		glm::uvec2 m_dimensions;
	};
}