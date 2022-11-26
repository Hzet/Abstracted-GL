#include "agl/graphics/texture/texture2d.hpp"
#include "agl/graphics/texture/texture-manager.hpp"
#include "agl/system/debug/error.hpp"
#include "agl/system/glcore/gl-core.hpp"

#include <stb_image.hpp>

namespace agl
{
	texture_2d::texture_2d()
		: texture_base{ TEXTURE_2D }
	{
	}

	bool texture_2d::load_from_file(const std::string &filepath)
	{
		auto w = std::int32_t{};
		auto h = std::int32_t{};
		auto channels = std::int32_t{};

		stbi_set_flip_vertically_on_load(true);

		auto *data = static_cast<unsigned char*>(stbi_load(filepath.c_str(), &w, &h, &channels, 0));

		if (data == nullptr)
		{
			AGL_CORE_WARNING("Failed to load the texture from the file");
			stbi_image_free(data);
			return false;
		}

		m_size.x = w;
		m_size.y = h;
		m_size.z = 0.f;
		m_filepath = filepath;

		auto format = std::uint32_t{};
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		create();
		bind();

		AGL_CALL(glTexImage2D(get_type(), 0u, format, w, h, 0, format, GL_UNSIGNED_BYTE, data));
		AGL_CALL(glGenerateMipmap(get_type()));

		stbi_image_free(data);
		return true;
	}
}