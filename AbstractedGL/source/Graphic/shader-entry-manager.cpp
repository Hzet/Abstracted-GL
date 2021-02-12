#include "shader-entry-manager.hpp"

namespace agl
{
	void CShaderEntryManager::createEntry(const std::string &name, const CShaderUID &shaderUID)
	{
		entries_.emplace(std::pair{ name, shaderUID });
	}

	void CShaderEntryManager::redirectEntry(const std::string &name, const CShaderUID &shaderUID)
	{
		entries_.at(name) = shaderUID;
	} 

	void CShaderEntryManager::reset()
	{
		entries_.clear();
	}

}