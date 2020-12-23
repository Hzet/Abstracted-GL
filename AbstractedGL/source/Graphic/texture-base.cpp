#include "texture-base.hpp"
#include "texture-slot.hpp"
#include "../System/gl-core.hpp"

namespace agl
{
	namespace graphics
	{

		CTextureBase::CTextureBase(const std::uint64_t target)
			: target_(target)
		{
		}

		CTextureBase::~CTextureBase()
		{
			if (isMoveConstructing())
				destroy();
		}

		std::uint64_t CTextureBase::getTarget() const
		{
			return target_;
		}

		std::uint32_t CTextureBase::getSlotNumber() const
		{
			return textureSlot_;
		}

		void CTextureBase::setParameter(const std::uint64_t setting, const std::uint64_t value) const
		{
			AGL_CORE_ASSERT(isCreated(), "Can not set a parameter on non existing texture!");

			bind();
			//AGL_CALL(glBindTexture(getTarget(), objectID_));
			AGL_CALL(glTexParameteri(target_, setting, value));
		}

		void CTextureBase::create()
		{
			AGL_CALL(glGenTextures(1u, &objectID_));

			textureSlot_ = graphics::CTextureSlot::Register();
		}

		void CTextureBase::destroy()
		{
			if (!isCreated())
				return;
			
			AGL_CALL(glDeleteTextures(1u, &objectID_));

			graphics::CTextureSlot::Unregister(textureSlot_);
			textureSlot_ = 0u;
			objectID_ = 0u;
		}

		void CTextureBase::bind() const
		{
			AGL_CALL(glActiveTexture(GL_TEXTURE0 + textureSlot_));
			AGL_CALL(glBindTexture(target_, objectID_));
		}

		void CTextureBase::unbind() const
		{
			AGL_CALL(glBindTexture(target_, 0u));
		}
	}
}