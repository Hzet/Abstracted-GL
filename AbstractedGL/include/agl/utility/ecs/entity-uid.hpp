#pragma once
#include "utility/ecs/config.hpp"
#include "utility/unique-identifier.hpp"

namespace agl
{
	class entity;

	class entity_uid final
		: public TUID<entity, AGL_MAX_ENTITIES>
	{
	public:
		using TUID<entity, AGL_MAX_ENTITIES>::TUID;
	};
}

namespace std
{
	template <>
	struct hash<agl::entity_uid>
	{
		size_t operator()(const agl::entity_uid &uid) const noexcept
		{
			return hash<uint64_t>{}(static_cast<const uint64_t>(uid));
		}
	};
}