#pragma once
#include "agl/uid/static-unique-identifier.hpp"

namespace agl
{
	class texture_base;

	using texture_uid = TStaticUID<texture_base>;
}
namespace std
{
	/// <summary>
	/// The specialized hasher structure.
	/// </summary>
	template <>
	struct hash<agl::texture_uid>
	{
		size_t operator()(agl::texture_uid& const uid) const noexcept
		{
			return hash<uint64_t>{}(static_cast<const uint64_t>(uid));
		}
	};
}
