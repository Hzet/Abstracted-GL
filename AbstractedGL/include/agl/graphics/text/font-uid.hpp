#pragma once
#include "agl/uid/static-unique-identifier.hpp"

namespace agl
{
	class font;

	using font_uid = TStaticUID<font>;
}
namespace std
{
	/// <summary>
	/// The specialized hasher structure.
	/// </summary>
	template <>
	struct hash<agl::font_uid>
	{
		size_t operator()(agl::font_uid& const uid) const noexcept
		{
			return hash<uint64_t>{}(static_cast<const uint64_t>(uid));
		}
	};
}
