#pragma once
#include "utility/ecs/component-array.hpp"
#include "utility/ecs/entity-uid.hpp"
#include "utility/ecs/signature.hpp"
#include "utility/ecs/registry-component.hpp"

namespace agl
{
	/// <summary>
	/// A view class representing a container that accumulates the entities matching sig with 'Args'.
	/// </summary>
	template <typename... Args>
	class view final
	{
	public:
		/// <summary>
		/// The view's forward iterator.
		/// </summary>
		class iterator
		{
		public:
			using value_type = registry_component::TComponent<Args...>;
			using iterator_category = std::input_iterator_tag;
			using difference_type = std::uint64_t;
			using pointer = std::conditional_t<sizeof...(Args) == 1, std::tuple_element_t<0, std::tuple<Args*...>>, std::tuple<Args*...>>;
			using reference = value_type;

			explicit iterator(view<Args...> &view, std::vector<entity_uid>::iterator it);

			iterator& operator++();
			iterator operator++(int);

			reference operator*();

			pointer operator->();

			bool operator==(const iterator &other) const;
			bool operator!=(const iterator &other) const;

			const entity_uid& get_entity_uid() const;

		private:
			view<Args...> &m_view;

			std::vector<entity_uid>::iterator m_iterator;
		};
		
	public:
		//view();
		view(view&&) = default;
		view(view const& other) = delete;
		view& operator=(view&&) = default;
		view& operator=(view const& other) = delete;
		~view();

		/// <summary>
		/// Return an iterator pointing to the first element of the view.
		/// </summary>
		/// <returns>The begin iterator</returns>
		iterator begin();

		/// <summary>
		/// Return an iterator pointing to the element after the last element of the view.
		/// </summary>
		/// <returns>The end iterator</returns>
		iterator end();

		std::uint64_t get_count() const;

		bool needs_update() const;

	private:
		friend class registry;

		/// <summary>
		/// Construct from component array references.
		/// </summary>
		/// <param name="arrays">The component arrays</param>
		view(std::tuple<component_array<Args>*...> arrays);

		/// <summary>
		/// Adds the entities belonging to the view.
		/// </summary>
		/// <param name="entities"></param>
		void track(std::vector<entity_uid> &&entities);

		/// <summary>
		/// Returns a tuple of references to queried e's components.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		/// <returns>The components</returns>
		registry_component::TComponent<Args...> get(const entity_uid &id_entity);

		/// <summary>
		/// Implementation of 'get' method.
		/// </summary>
		/// <param name="id_entity"></param>
		/// <param name=""></param>
		/// <returns></returns>
		template <std::uint64_t... Sequence> 
		registry_component::TComponent<Args...> get_impl(const entity_uid &id_entity, std::index_sequence<Sequence...>);

		template <std::uint64_t... Sequence>
		bool needs_update_impl(std::index_sequence<Sequence...>) const;

		template <std::uint64_t... Sequence>
		void null_arrays(std::index_sequence<Sequence...>);

	private:
		std::vector<entity_uid> m_entities;
		std::tuple<component_array<Args>*...> m_arrays;
	};

#include "utility/ecs/view.inl"
}