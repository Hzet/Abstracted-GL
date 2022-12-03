#include "agl/graphics/text/font-manager.hpp"
#include "agl/core/misc/log.hpp"
#include "agl/system/debug/assert.hpp"

namespace agl
{
	font_uid font_manager::load_from_file(std::string const& filepath)
	{
		if (m_filepath_to_id.find(filepath) != m_filepath_to_id.cend())
			return m_filepath_to_id.at(filepath);

		auto font = agl::font{};

		if (!font.load_from_file(filepath))
		{
			AGL_CORE_LOG_WARNING(false, "Failed to load font \"{}\"", filepath);
			return font_uid{};
		}

		font.m_id_font = font_uid::create();

		return font.get_id();
	}

	font const& font_manager::get_font(font_uid id_font) const
	{
		AGL_CORE_ASSERT(id_font <= m_fonts.size(), "Index out of bounds: font \"{}\" not present", id_font);

		return m_fonts[id_font - 1];
	}
}