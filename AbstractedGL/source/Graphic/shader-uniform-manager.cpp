#include "shader-uniform-manager.hpp"

namespace agl
{
	void CUniformManager::create(const std::string &name, const CShaderUID &shaderUID)
	{
		entries_.emplace(std::pair{ name, shaderUID });
	}

	void CUniformManager::redirect(const std::string &name, const CShaderUID &shaderUID)
	{
		entries_.at(name) = shaderUID;
	}

	const CShaderUID& CUniformManager::getShaderOf(const std::string &name) const
	{
		return entries_.at(name);
	}

	void CUniformManager::reset()
	{
		entries_.clear();
	}

	const std::unordered_map<std::string, agl::CShaderUID>& CUniformManager::getEntries() const
	{
		return entries_;
	}

}