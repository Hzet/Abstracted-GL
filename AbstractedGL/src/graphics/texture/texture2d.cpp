#include "graphics/texture/texture2d.hpp"
#include "graphics/texture/texture-atlas.hpp"
#include "system/debug/error.hpp"
#include "system/glcore/gl-core.hpp"

#include <stb_image.hpp>

namespace agl
{
	texture_2d::texture_2d()
	{
	}

	const glm::uvec2& texture_2d::get_dimensions() const
	{
		return m_dimensions;
	}

	bool texture_2d::load_from_file(const std::string &filename)
	{
		auto w = std::int32_t{};
		auto h = std::int32_t{};
		auto channels = std::int32_t{};

		stbi_set_flip_vertically_on_load(true);

		auto *data = static_cast<unsigned char*>(stbi_load(filename.c_str(), &w, &h, &channels, 0));

		if (data == nullptr)
		{
			AGL_CORE_WARNING("Failed to load the texture from the file");
			stbi_image_free(data);
			return false;
		}

		m_dimensions.x = w;
		m_dimensions.y = h;

		auto format = std::uint32_t{};
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		create();
		bind();

		AGL_CALL(glTexImage2D(get_target(), 0u, format, w, h, 0, format, GL_UNSIGNED_BYTE, data));
		AGL_CALL(glGenerateMipmap(get_target()));

		stbi_image_free(data);
		return true;
	}

	texture_type texture_2d::get_target() const
	{
		return TEXTURE_2D;
	}
}