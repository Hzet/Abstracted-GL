#pragma once
#include <functional>

#include "agl/utility/static-unique-identifier.hpp"

namespace agl
{
	class shader;

	/// <summary>
	/// The unique identifier for shaders.
	/// </summary>
	using shader_uid = TStaticUID<shader>;
}

namespace std
{
	/// <summary>
	/// The specialized hasher structure.
	/// </summary>
	template <>
	struct hash<agl::shader_uid>
	{
		size_t operator()(const agl::shader_uid &uid) const noexcept
		{
			return hash<uint64_t>{}(static_cast<const uint64_t>(uid));
		}
	};
}