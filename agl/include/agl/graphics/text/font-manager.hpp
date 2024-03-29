#pragma once
#include <unordered_map>

#include "agl/graphics/text/font.hpp"
#include "agl/graphics/text/font-uid.hpp"

namespace agl
{
	class font_manager
	{
	public:
		font_uid load_from_file(std::string const& filepath, std::uint64_t size);

		font const& get_font(font_uid id_font) const;

	private:
		std::vector<font> m_fonts;
		std::unordered_map<std::string, font_uid> m_filepath_to_id;
	};
}