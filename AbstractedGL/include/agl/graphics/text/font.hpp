#pragma once
#include <vector>
#include "agl/graphics/text/glyph.hpp"
#include "agl/graphics/text/font-uid.hpp"
#include "agl/graphics/texture/texture2d.hpp"

namespace agl
{
	class font
	{
	public:
		bool load_from_file(std::string const& filepath, std::uint64_t size);

		std::string const& get_filepath() const;

		glyph const& get_glyph(char ch) const; 

		font_uid get_id() const;

	private:
		friend class font_manager;

	private:
		std::string m_filepath;
		std::vector<glyph> m_glyphs;
		font_uid m_id_font;
	};
}