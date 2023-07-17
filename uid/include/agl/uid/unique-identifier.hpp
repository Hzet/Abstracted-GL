#pragma once
#include "agl/uid/unique-identifier-manager.hpp"

namespace agl
{
	/// <summary>
	/// Helper template class to create a register of unique identifiers for a dummy template typename T.
	/// </summary>
	template <typename T, std::uint64_t Size = 1024ul>
	class unique_id
	{
	public:
		/// <summary>
		/// A struct to inform that the unique identifier shall not be created during construction.
		/// </summary>
		enum invalid_type
		{
			INVALID = 0ul
		};

	public:
		static unique_id create();

		static std::uint64_t get_reference_count(const unique_id &uid);

	public:
		/// <summary>
		/// Registers the unique identifier for this instance.
		/// </summary>
		unique_id();

		/// <summary>
		/// Creates the instance but postpones the registration of the unique identifier.
		/// </summary>
		/// <param name="">The invalid type</param>
		unique_id(invalid_type);

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">the other object</param>
		unique_id(unique_id &&other);

		/// <summary>
		/// Increases the unique identifier's references count.
		/// </summary>
		/// <param name="other">the other object</param>
		unique_id(const unique_id &other);

		/// <summary>
		/// Unregister the unique identifier.
		/// </summary>
		virtual ~unique_id();

		/// <summary>
		/// Swap the identifiers.
		/// </summary>
		/// <param name="other">the other object</param>
		/// <returns>reference to *this</returns>
		unique_id& operator=(unique_id &&other);

		/// <summary>
		/// Increases the unique identifier's references count.
		/// </summary>
		/// <param name="other">the other object</param>
		unique_id& operator=(const unique_id &other);

		/// <summary>
		/// Implicit cast operator.
		/// </summary>
		/// <returns>The unique identifier's value</returns>
		operator std::uint64_t() const;

	private:
		static CUIDManager& get_manager();

	private:
		unique_id(std::uint64_t id);

	private:
		std::uint64_t m_id;
	};

#include "agl/uid/unique-identifier.inl"
}