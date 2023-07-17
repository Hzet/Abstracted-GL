#include "agl/graphics/texture/texture2d.hpp"
#include "agl/graphics/texture/texture-manager.hpp"
#include "agl/debug/error.hpp"
#include "agl/system/glcore/gl-core.hpp"

#include <stb_image.hpp>

namespace agl
{
	texture_2d::texture_2d()
		: texture_base{ TEXTURE_2D }
	{
	}


	void texture_2d::load_from_memory(glm::vec2 const& size, std::byte const * const buffer)
	{
		m_size = glm::vec3{ size, 0.f };
		
		create();
		bind();

		set_parameters();

		AGL_CALL(glTexImage2D(get_type(), 0, GL_RED, size.x, size.y, 0, GL_RED, GL_UNSIGNED_BYTE, buffer));

		if (get_parameters().create_mipmaps)
			AGL_CALL(glGenerateMipmap(get_type()));

		unbind();
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
			set_format_type(TEXTURE_FORMAT_RED);
		else if (channels == 3)
			set_format_type(TEXTURE_FORMAT_RGB);
		else if (channels == 4)
			set_format_type(TEXTURE_FORMAT_RGBA);

		create();
		bind();

		set_parameters();

		/*AGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		AGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		AGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		AGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));*/

		AGL_CALL(glTexImage2D(get_type(), 0u, get_format_type(), m_size.x, m_size.y, 0, get_format_type(), GL_UNSIGNED_BYTE, data));

		if(get_parameters().create_mipmaps)
			AGL_CALL(glGenerateMipmap(get_type()));

		unbind();
		stbi_image_free(data);

		return true;
	}
}