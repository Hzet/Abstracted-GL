#pragma once
#include "utility/unique-identifier.hpp"

namespace agl
{	
	class texture_base;

	/// <summary>
	/// The unique identifier for shaders.
	/// </summary>
	class texture_uid
		: public TUID<texture_base>
	{
	public:
		using TUID<texture_base>::TUID;
	};
}

namespace std
{
	/// <summary>
	/// The specialized hasher structure.
	/// </summary>
	template <>
	struct hash<agl::texture_uid>
	{
		size_t operator()(const agl::texture_uid &uid) const noexcept
		{
			return hash<uint64_t>{}(static_cast<const uint64_t>(uid));
		}
	};
}
