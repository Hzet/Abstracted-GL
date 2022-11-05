#pragma once
#include <vector>

namespace agl
{
	template <typename T>
	class ordered_list
	{
	public:
		class element
		{
		public:
			element();

			bool has_element(T element) const;
			bool insert_after(T prev, T next);
			bool insert_before(T prev, T next);
			void clear();
			std::uint64_t get_count() const;
			const T& get_element() const;
			const std::vector<element> get_sub_elements() const;

		private:
			template <typename TType> element(TType value);

			std::vector<element> m_sub_elements;
			std::uint64_t m_count;
			T m_element;
		};

	public:
		void clear();
		void order();
		bool is_valid() const;

		void insert_after(T prev, T next);
		void insert_before(T prev, T next);

		std::uint64_t get_count();
		const element& get_head();

	private:
		std::vector<std::pair<T, T>> m_disconnected;
		element m_list;
	};

#include "agl/utility/ordered-list.inl"
}