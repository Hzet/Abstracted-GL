#pragma once
#include <vector>

namespace agl
{
	class entity_uid;

	/// <summary>
	/// A base polymorphic base class for component_array class.
	/// </summary>
	class component_array_base
	{
	public:
		/// <summary>
		/// Defaulted virtual destructor.
		/// </summary>
		virtual ~component_array_base() = default;

		/// <summary>
		/// Returns the count of currently stored elements
		/// </summary>
		/// <returns>The count</returns>
		std::uint64_t get_count() const;

		/// <summary>
		/// Virtual method to destroy an e's component without the need to know the component's type.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		virtual void on_entity_destroy(const entity_uid &id_entity) = 0;

	private:
		friend class std::vector<component_array_base>;
		template <typename T> friend class component_array;

		std::uint64_t m_count;
	};
}