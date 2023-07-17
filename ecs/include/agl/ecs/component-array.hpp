#pragma once
#include <array>

#include "agl/debug/assert.hpp"
#include "agl/ecs/config.hpp"
#include "agl/ecs/component-array-base.hpp"
#include "agl/ecs/component-type-uid.hpp"
#include "agl/ecs/entity-uid.hpp"

namespace agl
{
	/// <summary>
	/// An array object that stores the components and it's relation with entities.
	/// </summary>
	template <typename T>
	class component_array final
		: public component_array_base
	{
	public:
/*
		/// <summary>
		/// Self insert constructor.
		/// Constructs the object and insert the pointer to itself into the 'destination'.
		/// </summary>
		/// <param name="destination">The destination</param>
		component_array(std::array<component_array_base*, AGL_MAX_COMPONENTS> &destination);*/

		/// <summary>
		/// Initialize the component with 'args' and then attach to an e aliased as 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <param name="...args">The initialization arguments</param>
		/// <returns>The newly created component</returns>
		template <typename... Args> 
		T& attach(const entity_uid &id_entity, Args&&... args);

		/// <summary>
		/// Default constructs a component and relate it to the e aliased as 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The newly created component</returns>
		T& attach(const entity_uid &id_entity);

		/// <summary>
		/// Detach component from e aliased as 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		void detach(const entity_uid &id_entity);

		/// <summary>
		/// Returns the component related to e aliased as 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The component</returns>
		T& get(const entity_uid &id_entity);

		/// <summary>
		/// Returns the component related to e aliased as 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The component</returns>
		const T& get(const entity_uid &id_entity) const;

	private:
		/// <summary>
		/// Converts e's unique identifier to array index.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The index of the e</returns>
		std::uint64_t get_index(const entity_uid &id_entity) const;

		/// <summary>
		/// Overridden virtual method to destroy an e's component without the need to know the component's type.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		virtual void on_entity_destroy(const entity_uid &id_entity) override;

	private:
		std::array<T, AGL_MAX_ENTITIES> m_components;
		std::array<bool, AGL_MAX_ENTITIES> m_active_entities;
	};

#include "agl/ecs/component-array.inl"
}