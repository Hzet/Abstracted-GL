#pragma once
#include <cstdint>
#include <list>
#include <vector>

namespace agl
{
	class CUIDManager
	{
		template <typename T, std::uint64_t Size>
		friend class unique_id;
		
		/// <summary>
		/// Returns an index corresponding to the 'uid'.
		/// </summary>
		/// <param name="uid">The unique identifier</param>
		/// <returns>The index</returns>
		static std::uint64_t get_index(std::uint64_t uid);

		/// <summary>
		/// uniform_register the unique identifier.
		/// </summary>
		/// <returns>The unique identifier's value</returns>
		std::uint64_t create();

		/// <summary>
		/// Unregister the unique identifier.
		/// </summary>
		/// <param name="uid">The unique identifier's value</param>
		void destroy(std::uint64_t uid);

		/// <summary>
		/// Increments the count of active 'uid'
		/// </summary>
		/// <param name="uid">The unique identifier</param>
		void increment(std::uint64_t uid);

		std::uint64_t get_references_count(std::uint64_t uid) const;

		CUIDManager(std::uint64_t count);

		std::uint64_t m_count;
		std::list<std::uint64_t> m_free_indexes;
		std::uint64_t m_peak;
		std::vector<std::uint64_t> m_registered;
	};
}