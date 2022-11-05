#pragma once
#include "agl/utility/unique-identifier.hpp"

namespace agl
{	
	class texture_base;

	/// <summary>
	/// The unique identifier for shaders.
	/// </summary>
	class texture_uid
		: public unique_id<texture_base>
	{
	public:
		using unique_id<texture_base>::unique_id;
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
