#include "texture-base.hpp"
#include "../System/gl-core.hpp"

namespace agl
{
	ITexture::~ITexture()
	{
		if (isMoveConstructing())
			destroy();
	}


	const CTextureUID ITexture::getUID() const
	{
		return uid_;
	}


	std::string ITexture::getFilepath() const
	{
		return directory_ + filename_;
	}


	const std::string & ITexture::getFilename() const
	{
		return filename_;
	}


	const std::string & ITexture::getDirectory() const
	{
		return directory_;
	}

	void ITexture::setParameter(const std::uint64_t setting, const std::uint64_t value) const
	{
		AGL_CORE_ASSERT(isCreated(), "Can not set a parameter on non existing texture!");

		bind();
		AGL_CALL(glTexParameteri(getTarget(), setting, value));
	}

	void ITexture::create()
	{
		AGL_CALL(glGenTextures(1u, &objectID_));
	}

	void ITexture::destroy()
	{
		if (!isCreated())
			return;

		AGL_CALL(glDeleteTextures(1u, &objectID_));

		objectID_ = 0u;
	}

	void ITexture::bind() const
	{
		AGL_CALL(glBindTexture(getTarget(), objectID_));
	}

	void ITexture::unbind() const
	{
		AGL_CALL(glBindTexture(getTarget(), 0u));
	}

	void ITexture::setFilepath(const std::string &filepath)
	{
		std::uint64_t found = filepath.find_last_of('/');

		if (found == std::string::npos)
			filename_ = filepath;
		else
		{
			directory_ = filepath.substr(0, found);
			filename_ = filepath.substr(found + 1u);
		}
	}

}