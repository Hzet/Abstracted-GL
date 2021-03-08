#pragma once

#include <glm/glm.hpp>
#include "texture-base.hpp"

namespace agl
{
	/// <summary>
	/// 2D texture
	/// </summary>
	class CTexture2D
		: public ITexture
	{
	public:
		static CTexture2D LoadFromFile(const std::string &filepath);

		using ITexture::ITexture;

		/// <summary>
		/// Set dimensions to 0.
		/// </summary>
		CTexture2D();

		/// <summary>
		/// Get dimensions
		/// </summary>
		/// <returns>
		/// The dimensions
		/// </returns>
		const glm::uvec2& getDimensions() const;

		/// <summary>
		/// Loads the texture from a file.
		/// </summary>
		/// <param name="filename">The filepath</param>
		/// <returns>
		/// True - texture loaded successfully
		/// False - failed to load the texture
		/// </returns>
		bool loadFromFile(const std::string &filename);

		virtual std::uint64_t getTarget() const override;

	private:
		glm::uvec2 dimensions_;
	};
}