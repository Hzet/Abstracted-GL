#include "shader-manager.hpp"

namespace agl
{
	CShaderManager::CShaderManager(const CShaderUID &uid, CShader &&shader)
	{
		AddShader(uid, std::forward<CShader>(shader));
	}

	const agl::CShader& CShaderManager::GetShader(const CShaderUID &uid)
	{
		return GetShaders().at(uid);
	}

	void CShaderManager::AddShader(const CShaderUID &uid, CShader &&shader)
	{
		GetShaders()[uid] = std::move(shader);
	}

	bool CShaderManager::LinkAllShaders()
	{
		for (auto &m : GetShaders())
			if (!m.second.link())
				return false;

		return true;
	}

	std::unordered_map<CShaderUID, CShader>& CShaderManager::GetShaders()
	{
		static std::unordered_map<CShaderUID, CShader> Shaders_ = { };

		return Shaders_;
	}
}