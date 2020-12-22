#include "texture-slot.hpp"

#include "../System/gl-core.hpp"

namespace agl
{
	namespace graphics
	{
		std::vector<bool> CTextureSlot::Slots_ = std::vector<bool>(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, false);

		std::uint32_t CTextureSlot::Register()
		{
			for (std::uint32_t i = 0u; i < Slots_.size(); i++)
				if (!Slots_[i])
				{
					Slots_[i] = true;
					return i;
				}

			AGL_ASSERT(false, "Ran out of texture unit slots!");
			return 0u;
		}

		void CTextureSlot::Unregister(const std::uint32_t slot)
		{
			Slots_[slot] = false;
		}

		std::uint32_t CTextureSlot::GetMaxSlotCount()
		{
			return GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
		}

	}
}