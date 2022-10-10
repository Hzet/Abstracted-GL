#pragma once
#include "utility/unique-identifier-manager.hpp"

namespace agl
{
	/// <summary>
	/// Helper template class to create a register of unique identifiers for a dummy template typename T.
	/// </summary>
	template <typename T, std::uint64_t Size = 1024ul>
	class TUID
	{
	public:
		/// <summary>
		/// A struct to inform that the unique identifier shall not be created during construction.
		/// </summary>
		enum EInvalid
		{
			INVALID = 0ul
		};

		static std::uint64_t GetRefCount(const TUID &uid);

		/// <summary>
		/// Registers the unique identifier for this instance.
		/// </summary>
		TUID();

		/// <summary>
		/// Creates the instance but postpones the registration of the unique identifier.
		/// </summary>
		/// <param name="">The invalid type</param>
		TUID(EInvalid);

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">the other object</param>
		TUID(TUID &&other);

		/// <summary>
		/// Increases the unique identifier's references count.
		/// </summary>
		/// <param name="other">the other object</param>
		TUID(const TUID &other);

		/// <summary>
		/// Unregister the unique identifier.
		/// </summary>
		virtual ~TUID();

		/// <summary>
		/// Swap the identifiers.
		/// </summary>
		/// <param name="other">the other object</param>
		/// <returns>reference to *this</returns>
		TUID& operator=(TUID &&other);

		/// <summary>
		/// Increases the unique identifier's references count.
		/// </summary>
		/// <param name="other">the other object</param>
		TUID& operator=(const TUID &other);

		/// <summary>
		/// Implicit cast operator.
		/// </summary>
		/// <returns>The unique identifier's value</returns>
		operator std::uint64_t() const;

	private:
		static CUIDManager& get_manager();

		std::uint64_t m_id;
	};

#include "utility/unique-identifier.inl"
}