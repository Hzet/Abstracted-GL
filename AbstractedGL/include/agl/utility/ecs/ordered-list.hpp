#pragma once

#pragma once
#include <vector>

namespace agl
{
	template <typename T>
	class TOrderedList
	{
	public:
		TOrderedList();

		bool hasElement(T element) const;
		bool insertAfter(T prev, T next);
		bool insertBefore(T prev, T next);
		bool merge(TOrderedList other);
		void clear();
		std::uint64_t getCount() const;
		const T& getElement() const;
		const std::vector<TOrderedList<T>> getSubElements() const;

	private:
		template <typename TType> TOrderedList(TType value);

		std::vector<TOrderedList<T>> subelements_;
		std::uint64_t count_;
		T element_;
	};

	template <typename T>
	bool TOrderedList<T>::merge(TOrderedList other)
	{
		if (!insertAfter(other.getElement(), other.getSubElements()[0ul].getElement()))
			if (!insertBefore(other.getElement(), other.getSubElements()[0ul].getElement()))
				return false;

		return true;
	}

#include "utility/ecs/group-order.inl"
}