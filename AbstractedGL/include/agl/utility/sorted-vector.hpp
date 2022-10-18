#pragma once
#include <vector>

namespace agl
{
	template <typename TKey, typename TData>
	class sorted_vector
	{
	public:
		using const_iterator = typename std::vector<std::pair<TKey, TData>>::const_iterator;

		const_iterator begin() const;
		const_iterator end() const;

		std::uint64_t get_count() const;

		void erase(const_iterator iterator);

		const_iterator insert(TKey key, TData data);

		TData& get(std::uint64_t index);
		const TData& get(std::uint64_t index) const;

		const_iterator find(TKey key) const;

	private:
		std::vector<std::pair<TKey, TData>> m_vector;
	};

	template <typename TKey, typename TData>
	typename sorted_vector<TKey, TData>::const_iterator sorted_vector<TKey, TData>::begin() const
	{
		return m_vector.begin();
	}

	template <typename TKey, typename TData>
	typename sorted_vector<TKey, TData>::const_iterator sorted_vector<TKey, TData>::end() const
	{
		return m_vector.end();
	}

	template <typename TKey, typename TData>
	std::uint64_t sorted_vector<TKey, TData>::get_count() const
	{
		return m_vector.size();
	}

	template <typename TKey, typename TData>
	void sorted_vector<TKey, TData>::erase(const_iterator iterator)
	{
		m_vector.erase(iterator);
	}

	template <typename TKey, typename TData>
	typename sorted_vector<TKey, TData>::const_iterator sorted_vector<TKey, TData>::insert(TKey key, TData data)
	{
		std::pair<TKey, TData> pair;// = std::make_pair(key, data);
		pair.first = key;
		pair.second = data;

		if (get_count() == 0ul)
		{
			m_vector.push_back(pair);
			return m_vector.begin();
		}

		std::uint64_t l = 0ul;
		std::uint64_t r = get_count() - 1ul;
		std::uint64_t m;

		while (l <= r)
		{
			m = (l + r) / 2ul;

			const auto &mid = m_vector[m].first;

			if (r - l == 0ul)
			{
				if (mid < pair.first)
					m++;
				break;
			}
			else if (mid < pair.first)
				l = m + 1ul;
			else if (mid > pair.first)
				r = m - 1ul;
			else
				break;
		}

		return m_vector.insert(m_vector.begin() + m, pair);
	}

	template <typename TKey, typename TData>
	typename sorted_vector<TKey, TData>::const_iterator sorted_vector<TKey, TData>::find(TKey key) const
	{
		if (get_count() == 0ul)
			return m_vector.end();

		std::uint64_t l = 0ul;
		std::uint64_t r = get_count() - 1ul;
		std::uint64_t m;

		while (l <= r)
		{
			m = (l + r) / 2ul;

			const auto &mid = m_vector[m].first;

			if (mid < key)
				l = m + 1ul;
			else if (mid > key)
				r = m - 1ul;
			else
				return m_vector.begin() + m;
		}

		return m_vector.end();
	}

	template <typename TKey, typename TData>
	TData& sorted_vector<TKey, TData>::get(std::uint64_t index)
	{
		return m_vector[index];
	}

	template <typename TKey, typename TData>
	const TData& sorted_vector<TKey, TData>::get(std::uint64_t index) const
	{
		return m_vector[index];
	}
}

