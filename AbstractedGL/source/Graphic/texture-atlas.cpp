	#include "texture-atlas.hpp"

namespace agl
{
	CTextureUID CTextureAtlas::AddTexture2D(CTexture2D texture, const std::string &identifier)
	{
		if (HasTexture2D(identifier))
			return GetTextureUID(identifier);

		CTextureUID result;
		GetTextures2D().emplace(result, texture);
		GetDirectoryMap2D().emplace(identifier, result);

		return result;
	}

	bool CTextureAtlas::HasTexture2D(const std::string &filepath)
	{
		return GetDirectoryMap2D().find(filepath) != GetDirectoryMap2D().cend();
	}

	bool CTextureAtlas::HasTexture2D(const CTextureUID &textureUID)
	{
		return GetTextures2D().find(textureUID) != GetTextures2D().cend();
	}

	ITexture& CTextureAtlas::GetTexture(const CTextureUID &textureUID)
	{
		return GetTexture2D(textureUID);
	}

	CTextureUID CTextureAtlas::GetTextureUID(const std::string &filepath)
	{
		return GetDirectoryMap2D().find(filepath)->second;
	}

	CTexture2D& CTextureAtlas::GetTexture2D(const CTextureUID &textureUID)
	{
		return GetTextures2D().find(textureUID)->second;
	}

	agl::CTexture2D& CTextureAtlas::GetTexture2D(const std::string &filepath)
	{
		auto found = GetDirectoryMap2D().find(filepath);

		return GetTexture2D(found->second);
	}

	std::unordered_map<CTextureUID, CTexture2D>& CTextureAtlas::GetTextures2D()
	{
		static std::unordered_map<CTextureUID, CTexture2D> Textures2D_;

		return Textures2D_;
	}

	std::unordered_map<std::string, CTextureUID>& CTextureAtlas::GetDirectoryMap2D()
	{
		static std::unordered_map<std::string, CTextureUID> DirectoryMap2D_;

		return DirectoryMap2D_;
	}
}