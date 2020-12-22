#pragma once

#include <cstdint>
#include <vector>

namespace agl
{
	namespace graphics
	{
		class CTextureSlot
		{
		public:
			static std::uint32_t Register();
			static void Unregister(const std::uint32_t slot);

			static std::uint32_t GetMaxSlotCount();

		private:
			static std::vector<bool> Slots_;
		};
	}
}