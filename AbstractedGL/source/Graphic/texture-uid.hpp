#pragma once

#include "../System/unique-identifier.hpp"

namespace agl
{	
	/// <summary>
	/// The unique identifier for shaders.
	/// </summary>
	class CTextureUID
		: public system::TUID<CTextureUID>
	{
	public:
		using system::TUID<CTextureUID>::TUID;
	};
}

namespace std
{
	/// <summary>
	/// The specialized hasher structure.
	/// </summary>
	template <>
	struct hash<agl::CTextureUID>
	{
		size_t operator()(const agl::CTextureUID &uid) const noexcept
		{
			return hash<uint64_t>{}(static_cast<const uint64_t>(uid));
		}
	};
}