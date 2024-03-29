#pragma once
#include <vector>
#include "agl/ecs/entity-uid.hpp"
namespace agl
{
	/// <summary>
	/// A base polymorphic base class for component_array class.
	/// </summary>
	class component_array_base
	{
	public:
		component_array_base();

		/// <summary>
		/// Defaulted virtual destructor.
		/// </summary>
		virtual ~component_array_base() = default;

		/// <summary>
		/// Returns the count of currently stored elements
		/// </summary>
		/// <returns>The count</returns>
		std::uint64_t get_count() const;

		bool has_changed() const;

		/// <summary>
		/// Virtual method to destroy an e's component without the need to know the component's type.
		/// </summary>
		/// <param name="id_entity">The e's unique identifier</param>
		virtual void on_entity_destroy(const entity_uid &id_entity) = 0;

	protected:
		//friend class std::vector<component_array_base>;

		bool m_changed;
		std::uint64_t m_count;

	private:
		friend class registry_component;
	};
}