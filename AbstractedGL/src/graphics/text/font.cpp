#include "agl/system/glcore/gl-core.hpp"
#include "agl/graphics/text/font.hpp"
#include "agl/graphics/texture/texture2d.hpp"
#include "agl/system/debug/error.hpp"
#include "agl/system/debug/exceptions.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H  

namespace agl
{
	bool font::load_from_file(std::string const& filepath, std::uint64_t size)
	{
		m_filepath = filepath;

		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			AGL_CORE_EXCEPTION(ExFreeTypeInit, "");
		}

		FT_Face face;
		if (FT_New_Face(ft, filepath.c_str(), 0, &face))
			return false;

		FT_Set_Pixel_Sizes(face, 0, size);

		AGL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); // disable byte-alignment restriction

		for (auto ch = 0; ch < 256; ++ch)
		{
			if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
			{
				AGL_CORE_LOG_WARNING("Character \"{}\" failed to load", ch);
				continue;
			}

			auto texture = texture_2d{};

			texture.set_format_type(TEXTURE_FORMAT_RED);
			texture.set_size_filters(TEXTURE_PIXEL_LINEAR, TEXTURE_PIXEL_LINEAR);
			texture.set_texture_wrap(TEXTURE_WRAP_CLAMP_TO_EDGE, TEXTURE_WRAP_CLAMP_TO_EDGE, TEXTURE_WRAP_NONE);
			texture.load_from_memory({ face->glyph->bitmap.width, face->glyph->bitmap.rows }, reinterpret_cast<std::byte*>(face->glyph->bitmap.buffer));

			auto g = glyph{
				static_cast<std::uint64_t>(face->glyph->advance.x),
				glm::ivec2{face->glyph->bitmap_left, face->glyph->bitmap_top},
				static_cast<char>(ch),
				std::move(texture)
			};

			m_glyphs.push_back(g);
		}

		//AGL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 0));

		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		return true;
	}

	std::string const& font::get_filepath() const
	{
		return m_filepath;
	}

	glyph const& font::get_glyph(char ch) const
	{
		AGL_ASSERT(ch <= m_glyphs.size(), "Index out of bounds: \"{}\" no such glyph", ch);

		return m_glyphs[static_cast<std::uint64_t>(ch)];
	}

	agl::font_uid font::get_id() const
	{
		return m_id_font;
	}
}