#pragma once
#include <array>
#include <memory>

#include "utility/ecs/component-array.hpp"

namespace agl
{
	/// <summary>
	/// Sub reg providing utility to manage the components.
	/// </summary>
	class registry_component_base
	{
	public:
		template <typename... Args>
		using TComponent = std::conditional_t<sizeof...(Args) == 1, std::tuple_element_t<0, std::tuple<Args&...>>, std::tuple<Args&...>>;

		/// <summary>
		/// Returns a reference or a tuple of references to the queried e's component..
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The component</returns>
		template <typename... Args> 
		TComponent<Args...> get(const entity_uid &id_entity);

	protected:
		virtual ~registry_component_base() = default;

		/// <summary>
		/// Constructs the component 'T' with 'args' and attaches it to 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <param name="...args">The construction arguments</param>
		/// <returns>The newly created component</returns>
		template <typename T, typename... Args> 
		T& attach_component(const entity_uid &id_entity, Args&&... args);

		/// <summary>
		/// Default constructs the components 'Args' and attaches them to 'id_entity'.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The newly created components</returns>
		template <typename... Args>
		TComponent<Args...> attach_component(const entity_uid &id_entity);

		/// <summary>
		/// Detaches the components 'Args' from the 'id_entity'
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		template <typename... Args>	
		void detach_component(const entity_uid &id_entity);

		/// <summary>
		/// Returns the references to queried component arrays.
		/// </summary>
		/// <returns>The component arrays</returns>
		template <typename... Args>	
		std::tuple<component_array<Args>&...> get_arrays();

		/// <summary>
		/// Implementation of 'get_array' method.
		/// </summary>
		/// <returns></returns>
		template <typename T> 
		component_array<T>& get_array();

		/// <summary>
		/// Returns the queried component array T in form of a polymorphic base class.
		/// </summary>
		/// <returns>A pointer to the component array base</returns>
		template <typename T> 
		component_array_base* get_array_base();

		/// <summary>
		/// Returns the count of currently stored elements in array aliased as 'arrayUID'.
		/// </summary>
		/// <param name="arrayUID">The component's type unique identifier</param>
		/// <returns>The count</returns>
		std::uint64_t get_array_count(std::uint64_t index) const;

		/// <summary>
		/// Detaches the all of the components of 'e'.
		/// </summary>
		/// <param name="e"></param>
		void on_entity_destroy(const entity &e);

	private:
		/// <summary>
		/// Implementation of 'attach_component' method.
		/// </summary>
		/// <param name="id_entity"></param>
		/// <param name=""></param>
		template <typename... Args, std::uint64_t... Sequence>
		std::tuple<Args&...> attach_component_impl(const entity_uid &id_entity, std::index_sequence<Sequence...>);

		/// <summary>
		/// Implementation of 'get_component' method.
		/// </summary>
		/// <param name="id_entity"></param>
		/// <param name=""></param>
		/// <returns></returns>
		template <typename... Args, std::uint64_t... Sequence>
		std::tuple<Args&...> get_component_impl(const entity_uid &id_entity, std::index_sequence<Sequence...>);

		/// <summary>
		/// Implementation of 'detach_component' method.
		/// </summary>
		/// <param name="id_entity"></param>
		/// <param name=""></param>
		template <typename... Args, std::uint64_t... Sequence>
		void detach_component_impl(const entity_uid &id_entity, std::index_sequence<Sequence...>);

		/// <summary>
		/// Implementation of 'get_array' method.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		template <typename... Args, std::uint64_t... Sequence>
		std::tuple<component_array<Args>&...> get_arrays_impl(std::index_sequence<Sequence...>);

		std::array<std::unique_ptr<component_array_base>, AGL_MAX_COMPONENTS> m_arrays;
	};

#include "utility/ecs/registry-component.inl"
}