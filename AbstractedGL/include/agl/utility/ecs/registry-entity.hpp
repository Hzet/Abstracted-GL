#pragma once
#include <vector>

#include "agl/utility/ecs/entity-uid.hpp"
#include "agl/utility/ecs/signature.hpp"

namespace agl
{
	class registry;

	/// <summary>
	/// Sub reg providing utility to manage the entities.
	/// </summary>
	class registry_entity
	{
	public:
		/// <summary>
		/// Returns the e aliased as 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The e</returns>
		entity get_entity(const entity_uid &id_entity);

/*
		/// <summary>
		/// Checks whether the e has queried components.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>
		/// True - e has got all of the queried components attached.
		/// False - e has got some or all of the queried components absent.
		/// </returns>
		template <typename... Args> 
		bool has(const entity_uid &id_entity) const;
*/
	protected:
		registry_entity();
		virtual ~registry_entity() = default;

		/// <summary>
		/// Creates the e.
		/// </summary>
		/// <param name="reg">A pointer to the reg creating the e</param>
		/// <returns>The e</returns>
		entity create_entity(registry *reg);

		/// <summary>
		/// Destroys an e.
		/// </summary>
		/// <param name="e">The e</param>
		void destroy_entity(entity &e);

		/// <summary>
		/// Converts e's unique identifier to array index.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The index of the e</returns>
		std::uint64_t get_index(const entity_uid &id_entity) const;

		/// <summary>
		/// Get a reference of the sig of e alias as 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The sig</returns>
		signature& get_signature(const entity_uid &id_entity);

	private:
		friend class registry;

		std::vector<entity> m_entities;
	};

#include "agl/utility/ecs/registry-entity.hpp"
}