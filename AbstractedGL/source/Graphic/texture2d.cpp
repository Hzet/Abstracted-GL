#include "texture2d.hpp"
#include "texture-atlas.hpp"
#include "../System/gl-core.hpp"
#include "../System/error.hpp"
#include "../System/error-code.hpp"

#include <stb_image.hpp>

namespace agl
{
	CTextureUID CTexture2D::LoadFromFile(const std::string &filepath)
	{
		if (CTextureAtlas::HasTexture2D(filepath))
			return CTextureAtlas::GetTextureUID(filepath);

		CTexture2D result;
		result.loadFromFile(filepath);

		return CTextureAtlas::AddTexture2D(result, filepath);
	}

	CTexture2D::CTexture2D()
	{
	}

	const glm::uvec2& CTexture2D::getDimensions() const
	{
		return dimensions_;
	}

	bool CTexture2D::loadFromFile(const std::string &filename)
	{
		std::int32_t w, h, channels;

		stbi_set_flip_vertically_on_load(true);

		unsigned char *data = stbi_load(filename.c_str(), &w, &h, &channels, 0);

		if (data == nullptr)
		{
			AGL_CORE_ERROR("Failed to load the texture from the file", agl::error::READ_FILE);
			stbi_image_free(data);
			return false;
		}

		dimensions_.x = w;
		dimensions_.y = h;

		std::uint32_t format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		create();
		bind();

		AGL_CALL(glTexImage2D(getTarget(), 0u, format, w, h, 0, format, GL_UNSIGNED_BYTE, data));
		AGL_CALL(glGenerateMipmap(getTarget()));

		stbi_image_free(data);
		return true;
	}

	std::uint64_t CTexture2D::getTarget() const
	{
		return GL_TEXTURE_2D;
	}
}