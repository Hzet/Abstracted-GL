#include "utility/ecs/entity.hpp"

namespace agl
{
	entity::entity()
		: m_registry(nullptr)
		, m_id(entity_uid::INVALID)
	{
	}

	entity::entity(entity &&other)
		: m_registry(std::move(other.m_registry))
		, m_signature(std::move(other.m_signature))
		, m_id(std::move(other.m_id))
	{
	}

	entity::entity(const entity &other)
		: m_registry(other.m_registry)
		, m_signature(other.m_signature)
		, m_id(other.m_id)
	{
	}

	entity& entity::operator=(entity &&other)
	{
		m_registry = std::move(other.m_registry);
		m_signature = std::move(other.m_signature);
		m_id = std::move(other.m_id);

		return *this;
	}

	entity& entity::operator=(const entity &other)
	{
		m_registry = other.m_registry;
		m_signature = other.m_signature;
		m_id = other.m_id;

		return *this;
	}

	entity::~entity()
	{
		m_registry = nullptr;
	}

	const entity_uid& entity::get_entity_uid() const
	{
		return m_id;
	}

	entity::operator entity_uid() const
	{
		return m_id;
	}

	const signature& entity::get_signature() const
	{
		return m_signature;
	}

	entity::entity(registry *reg, const entity_uid &id_entity)
		: m_registry(reg)
		, m_id(id_entity)
	{
	}
}