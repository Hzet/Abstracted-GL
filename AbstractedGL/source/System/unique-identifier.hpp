#pragma once
#include <map>

namespace agl
{
	namespace system
	{
		/// <summary>
		/// Helper template class to create a register of unique identifiers for a dummy template typename T.
		/// </summary>
		template <typename T>
		class TUID
		{
		public:
			/// <summary>
			/// A struct to inform that the unique identifier shall not be created during construction.
			/// </summary>
			struct InvalidValue {};

			/// <summary>
			/// Registers the unique identifier for this instance.
			/// </summary>
			TUID();

			/// <summary>
			/// Creates the instance but postpones the registration of the unique identifier.
			/// </summary>
			/// <param name="">The invalid type</param>
			TUID(InvalidValue);

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
			/// <summary>
			/// Register the unique identifier.
			/// </summary>
			/// <returns>The unique identifier's value</returns>
			static std::uint64_t Register();

			/// <summary>
			/// Unregister the unique identifier.
			/// </summary>
			/// <param name="uid">The unique identifier's value</param>
			static void Unregister(TUID<T> &uid);

			/// <summary>
			/// Returns a reference to the registered identifiers.
			/// </summary>
			/// <returns></returns>
			static std::map<std::uint64_t, std::uint64_t>& RegisteredIdentifiers();

			/// <summary>
			/// Helper constructor.
			/// </summary>
			/// <param name="uid"></param>
			TUID(std::uint64_t uid);

			std::uint64_t uid_;
		};

#include "unique-identifier.inl"
	}
}