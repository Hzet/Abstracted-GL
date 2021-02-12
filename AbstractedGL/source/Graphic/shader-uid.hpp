#pragma once
#include "../System/unique-identifier.hpp"

namespace agl
{
	namespace graphics
	{
		/// <summary>
		/// The dummy type.
		/// </summary>
		struct SShaderUID {};
	}

	/// <summary>
	/// The unique identifier for shaders.
	/// </summary>
	using CShaderUID = system::CUID<graphics::SShaderUID>;
}

namespace std
{
	/// <summary>
	/// The specialized hasher structure.
	/// </summary>
	template <>
	struct hash<agl::CShaderUID>
	{
		size_t operator()(const agl::CShaderUID &uid) const noexcept
		{
			return hash<uint64_t>{}(static_cast<const uint64_t>(uid));
		}
	};
}