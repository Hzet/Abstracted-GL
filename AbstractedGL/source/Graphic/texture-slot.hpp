#pragma once

#include <cstdint>
#include <vector>

namespace agl
{
	namespace graphics
	{
		/// <summary>
		/// The class representing the texture slot that is an unique identifier.
		/// </summary>
		class CTextureSlot
		{
		public:

			/// <summary>
			/// Register and return the unique identifier.
			/// </summary>
			/// <returns>
			/// The unique identifier
			/// </returns>
			static std::uint32_t Register();

			/// <summary>
			/// Unregister the unique identifier
			/// </summary>
			/// <param name="slot">The unique identifier</param>
			static void Unregister(const std::uint32_t slot);

			/// <summary>
			/// Get the maximum slots count.
			/// </summary>
			/// <returns>
			/// The maximum slots count
			/// </returns>
			static std::uint32_t GetMaxSlotCount();

		private:
			static std::vector<bool> Slots_;
		};
	}
}