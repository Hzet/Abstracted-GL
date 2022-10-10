#include "utility/ecs/registry-entity.hpp"
#include "utility/ecs/registry.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	entity registry_entity::get_entity(const entity_uid &id_entity)
	{
		return m_entities[get_index(id_entity)];
	}

	registry_entity::registry_entity()
		: m_entities(AGL_MAX_ENTITIES)
	{
	}

	entity registry_entity::create_entity(registry *reg)
	{
		//AGL_CORE_ASSERT(occupied_ < AGL_MAX_ENTITIES, "Maximum capacity reached!");

		auto result = entity{ reg, entity_uid{ } };

		m_entities[get_index(result)] = result;

		return m_entities[get_index(result)];
	}

	void registry_entity::destroy_entity(entity &e)
	{
		m_entities[get_index(e)] = { };

		e = { };
	}

	std::uint64_t registry_entity::get_index(const entity_uid &id_entity) const
	{
		return id_entity - 1ul;
	}

	signature& registry_entity::get_signature(const entity_uid &id_entity)
	{
		return m_entities[get_index(id_entity)].m_signature;
	}

}