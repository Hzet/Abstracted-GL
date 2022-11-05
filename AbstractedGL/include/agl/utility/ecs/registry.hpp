#pragma once
#include "agl/utility/ecs/view.hpp"
#include "agl/utility/ecs/registry-entity.hpp"
#include "agl/utility/ecs/registry-component.hpp"
#include "agl/utility/ecs/registry-system.hpp"
#include "agl/core/app/resource.hpp"

namespace agl
{
	/// <summary>
	/// A coordinator class that combines of the features of all the base classes into one.
	/// </summary>
	class registry final
		: public resource_base
		, public registry_system
		, public registry_entity
		, public registry_component
	{
	public:

		/// <summary>
		/// Calls appropriate constructors.
		/// </summary>
		registry();

		/// <summary>
		/// Returns a view of entities that matches the sig of 'Args'.
		/// </summary>
		/// <returns>The view</returns>
		template <typename... Args> 
		view<Args...> strict_view();

		/// <summary>
		/// Returns a view of entities that the sig has at least the elements of sig of 'Args'.
		/// </summary>
		/// <returns>The view</returns>
		template <typename... Args> 
		view<Args...> inclusive_view();

		/// <summary>
		/// Creates an e.
		/// </summary>
		/// <returns>The e</returns>
		entity create();

		/// <summary>
		/// Destroys an e.
		/// </summary>
		/// <param name="e">The e</param>
		void destroy(entity &e);

		/// <summary>
		/// Update all of the active systems.
		/// </summary>
		void update();

	private:
		friend class entity;

		template <typename... Args> 
		friend class view;

		/// <summary>
		/// Returns a vector of entities matching the 'sig'
		/// </summary>
		/// <param name="sig">The sig of the components</param>
		/// <returns>The vector of entities</returns>
		std::vector<entity_uid> entities_matching(const signature &sig);

		std::vector<entity_uid> entities_including(const signature &sig);

		std::uint64_t max_inclusive_results(const signature &sig) const;

		/// <summary>
		/// Detaches the queried components from an e aliased as 'id_entity'.
		/// If the queried component was not attached to an e, 
		/// then no action will take place regarding that component array.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		template <typename... Args> 
		void detach(const entity_uid &id_entity);

		/// <summary>
		/// Initialize the component with 'args' and then attach to an e aliased as 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <param name="...args">The initialization arguments</param>
		/// <returns>The newly created component</returns>
		template <typename T, typename... Args> 
		T& attach(const entity_uid &id_entity, Args&&... args);

		/// <summary>
		/// Default initialize the component and attach it to 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The newly created components</returns>
		template <typename... Args> 
		registry_component::TComponent<Args...> attach(const entity_uid &id_entity);

	private:
		virtual void dummy() const override {};
	};

#include "agl/utility/ecs/registry.inl"
}