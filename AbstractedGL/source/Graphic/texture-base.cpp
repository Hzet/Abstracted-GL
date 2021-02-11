#include "texture-base.hpp"
#include "../System/gl-core.hpp"

namespace agl
{
	namespace graphics
	{
		ITextureBase::~ITextureBase()
		{
			if (isMoveConstructing())
				destroy();
		}

		void ITextureBase::setParameter(const std::uint64_t setting, const std::uint64_t value) const
		{
			AGL_CORE_ASSERT(isCreated(), "Can not set a parameter on non existing texture!");

			bind();
			AGL_CALL(glTexParameteri(getTarget(), setting, value));
		}

		void ITextureBase::create()
		{
			AGL_CALL(glGenTextures(1u, &objectID_));
		}

		void ITextureBase::destroy()
		{
			if (!isCreated())
				return;
			
			AGL_CALL(glDeleteTextures(1u, &objectID_));

			objectID_ = 0u;
		}

		void ITextureBase::bind() const
		{
			AGL_CALL(glBindTexture(getTarget(), objectID_));
		}

		void ITextureBase::unbind() const
		{
			AGL_CALL(glBindTexture(getTarget(), 0u));
		}

	}
}