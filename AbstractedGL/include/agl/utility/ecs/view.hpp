#pragma once
#include "utility/ecs/component-array.hpp"
#include "utility/ecs/entity-uid.hpp"
#include "utility/ecs/signature.hpp"
#include "utility/ecs/registry-component.hpp"

namespace agl
{
	template <typename... Args>
	class view
	{
	public:
		class iterator
		{
		public:
			iterator() = default;

			iterator& operator++();
			iterator operator++(int);

			entity_uid operator*() const;

			entity_uid const* const operator->() const;

			bool operator==(const iterator &other) const;
			bool operator!=(const iterator &other) const;

		private:
			template <typename... Args>
			friend class view;

		private:
			explicit iterator(view<Args...> const& view, std::vector<entity_uid>::const_iterator it);

		private:
			view<Args...> const& m_view;

			std::vector<entity_uid>::const_iterator m_iterator;
		private:
		};

	public:
		view(view&&) = default;
		view(view const& other) = delete;
		view& operator=(view&&) = default;
		view& operator=(view const& other) = delete;
		~view();

		iterator cbegin() const;
		iterator cend() const;

		std::uint64_t get_count() const;

		bool needs_update() const;

	private:
		friend class registry;

	private:
		view(std::tuple<component_array<Args>*...> arrays, std::vector<entity_uid>&& entities);

		template <std::uint64_t... Sequence>
		bool needs_update_impl(std::index_sequence<Sequence...>) const;

		template <std::uint64_t... Sequence>
		void null_arrays(std::index_sequence<Sequence...>);

	private:
		std::tuple<component_array<Args>*...> m_arrays;
		std::vector<entity_uid> m_entities;
	};

#include "utility/ecs/view.inl"
}