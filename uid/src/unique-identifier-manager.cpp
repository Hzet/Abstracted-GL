#include "agl/uid/unique-identifier-manager.hpp"

namespace agl
{
	std::uint64_t CUIDManager::get_index(std::uint64_t uid)
	{
		return uid - 1ul;
	}

	std::uint64_t CUIDManager::create()
	{
		m_count++;

		if (m_free_indexes.empty())
		{
			m_registered[m_peak]++;
			m_peak++;
			return m_peak;
		}
		else
		{
			auto index = m_free_indexes.front();
			m_free_indexes.pop_front();

			m_registered[index]++;

			return index + 1ul;
		}
	}

	void CUIDManager::destroy(std::uint64_t uid)
	{
		if (m_registered[get_index(uid)] == 1ul)
		{
			m_count--;

			if (m_count == 0ul)
			{
				m_free_indexes.clear();
				m_peak = 0ul;
			}
			else if (uid == m_peak)
				m_peak--;
			else if (uid < m_peak)
				m_free_indexes.push_front(uid);
		}

		m_registered[get_index(uid)]--;
	}

	void CUIDManager::increment(std::uint64_t uid)
	{
		if (uid == 0ul)
			return;

		m_registered[get_index(uid)]++;
	}

	std::uint64_t CUIDManager::get_references_count(std::uint64_t uid) const
	{
		return m_registered[get_index(uid)];
	}

	CUIDManager::CUIDManager(std::uint64_t count)
		: m_count(0ul)
		, m_peak(0ul)
		, m_registered(count, 0ul)
	{
	}
}