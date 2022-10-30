#pragma once
#include "utility/ecs/signature.hpp"
#include "utility/ecs/registry.hpp"

namespace agl
{
	/// <summary>
	/// An interface representing e.
	/// </summary>
	class entity
	{
	public:
		/// <summary>
		/// Default constructor.
		/// Sets the object to an invalid state.
		/// </summary>
		entity();

		/// <summary>
		/// Virtual destructor.
		/// </summary>
		virtual ~entity();

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		entity(entity &&other);

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		entity(const entity &other);

		/// <summary>
		/// Move assignment operator.
		/// </summary>
		/// <param name="other">The other object</param>
		/// <returns>Reference to *this</returns>
		entity& operator=(entity &&other);

		/// <summary>
		/// Copy assignment operator.
		/// </summary>
		/// <param name="other">The other object</param>
		/// <returns>Reference to *this</returns>
		entity& operator=(const entity &other);

		/// <summary>
		/// Returns the e's unique identifier.
		/// </summary>
		/// <returns>The e's unique identifier</returns>
		const entity_uid& get_entity_uid() const;

		/// <summary>
		/// Implicit cast operator to entity_uid.
		/// </summary>
		/// <returns>The e's unique identifier</returns>
		operator entity_uid() const;

		/// <summary>
		/// Returns the signature.
		/// </summary>
		/// <returns>The sig</returns>
		const signature& get_signature() const;

		/// <summary>
		/// Returns a reference or a tuple of references to the queried e's component.
		/// </summary>
		/// <returns>The component</returns>
		template <typename... Args> 
		registry::TComponent<Args...> get_component() const;

		/// <summary>
		/// Checks whether the e has queried components.
		/// </summary>
		/// <returns>
		/// True - e has got all of the queried components attached.
		/// False - e has got some or all of the queried components absent.
		/// </returns>
		template <typename... Args>
		bool has_component() const;

		/// <summary>
		/// Detaches the queried components from an e.
		/// If the queried component was not attached to an e, 
		/// then no action will take place regarding that component array.
		/// </summary>
		template <typename... Args> 
		void detach_component();
		
		/// <summary>
		/// Initialize the component with 'args' and then attach to an e aliased as 'id_entity'.
		/// </summary>
		/// <param name="...args">The initialization arguments</param>
		/// <returns>The newly created component</returns>
		template <typename T, typename... Args> 
		T& attach_component(Args&&... args);

		/// <summary>
		/// Default initialize the component and attach it to the e.
		/// </summary>
		/// <returns>The newly created component</returns>
		template <typename... Args>
		registry::TComponent<Args...> attach_component();

	private:
		friend class registry_entity;

		/// <summary>
		/// Construct from entity_uid.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		entity(registry *reg, const entity_uid &id_entity);

		registry *m_registry;
		signature m_signature;
		entity_uid m_id;
	};

#include "utility/ecs/entity.inl"
}