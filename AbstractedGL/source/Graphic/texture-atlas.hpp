#pragma once

#include <unordered_map>

#include "texture2d.hpp"

namespace agl
{
	/// <summary>
	/// A static / global container that stores textures.
	/// </summary>
	class CTextureAtlas
	{
	public:
		/// <summary>
		/// Returns any texture that 'textureUID' is assigned to.
		/// </summary>
		/// <param name="textureUID"></param>
		/// <returns></returns>
		static ITexture& GetTexture(const CTextureUID &textureUID);

		/// <summary>
		/// Returns the unique identifier of a texture loaded from 'filepath'.
		/// </summary>
		/// <param name="filepath">The texture's filepath</param>
		/// <returns>The texture's unique identifier</returns>
		static CTextureUID GetTextureUID(const std::string &filepath);

		/// <summary>
		/// Adds a 2D 'texture' to the container that will be identified with a 'identifier'
		/// and returns an unique identifier that has been assigned to this occurrance.
		/// </summary>
		/// <param name="texture">The texture</param>
		/// <param name="identifier">The identifier</param>
		/// <returns>The unique identifier</returns>
		static CTextureUID AddTexture2D(CTexture2D texture, const std::string &identifier);

		/// <summary>
		/// Returns a 2D texture that 'filepath' is assigned to.
		/// </summary>
		/// <param name="filepath">The texture's filepath</param>
		/// <returns>The 2D texture</returns>
		static CTexture2D& GetTexture2D(const std::string &filepath);

		/// <summary>
		/// Returns a 2D texture that 'textureUID' is assigned to.
		/// </summary>
		/// <param name="textureUID">The texture's unique identifier</param>
		/// <returns>The 2D texture</returns>
		static CTexture2D& GetTexture2D(const CTextureUID &textureUID);

		/// <summary>
		/// Checks whether the 2D texture from 'filepath' is present in the atlas.
		/// </summary>
		/// <param name="filepath">The texture's filepath</param>
		/// <returns>
		/// true - atlas contains the texture
		/// false - atlas does not contain the texture
		/// </returns>
		static bool HasTexture2D(const std::string &filepath);

		/// <summary>
		/// Checks whether the 2D texture identified with 'textureUID' is present in the atlas.
		/// </summary>
		/// <param name="textureUID">The texture's unique identifier</param>
		/// <returns>
		/// true - atlas contains the texture
		/// false - atlas does not contain the texture
		/// </returns>
		static bool HasTexture2D(const CTextureUID &textureUID);

	private:
		static std::unordered_map<CTextureUID, CTexture2D>& GetTextures2D();
		static std::unordered_map<std::string, CTextureUID>& GetDirectoryMap2D();
	};
}