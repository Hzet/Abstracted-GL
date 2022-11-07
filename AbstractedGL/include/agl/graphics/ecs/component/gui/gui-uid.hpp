#pragma once
#include "agl/utility/unique-identifier.hpp"

namespace agl
{
	class gui_base;

	using gui_uid = unique_id<gui_base>;
}


namespace std
{
	template <>
	struct hash<agl::gui_uid>
	{
		size_t operator()(const agl::gui_uid &uid) const noexcept
		{
			return hash<uint64_t>{}(static_cast<const uint64_t>(uid));
		}
	};
}