#pragma once
#include "../System/unique-identifier.hpp"

namespace agl
{
	/// <summary>
	/// The unique identifier for shaders.
	/// </summary>
	class CShaderUID
		: public system::TUID<CShaderUID>
	{
	public:
		using system::TUID<CShaderUID>::TUID;
	};
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