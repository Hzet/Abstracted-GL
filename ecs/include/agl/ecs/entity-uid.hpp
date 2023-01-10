#pragma once
#include "agl/ecs/config.hpp"
#include "agl/uid/unique-identifier.hpp"

namespace agl
{
	class entity;

	using entity_uid = unique_id<entity, AGL_MAX_ENTITIES>;
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