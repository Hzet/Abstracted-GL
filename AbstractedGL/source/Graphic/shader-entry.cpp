#include "shader-entry.hpp"
#include "default-agl-shaders.hpp"

namespace agl
{
	const std::string& IShaderEntry::getName() const
	{
		return name_;
	}

	void IShaderEntry::setName(const std::string &name)
	{
		reset();
		name_ = name;
	}

	void IShaderEntry::attachEntry(const std::string &name, const CShaderUID &shaderUID)
	{
		createEntry(name_ + "." + name, shaderUID);
	}

	void IShaderEntry::redirectEntry(const std::string &name, const CShaderUID &shaderUID)
	{
		CShaderEntryManager::redirectEntry(name_ + "." + name, shaderUID);
	}
}