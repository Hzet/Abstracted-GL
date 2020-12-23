#include "renderer.hpp"

#include "../System/gl-core.hpp"

namespace agl
{
	void CRenderer::draw(const CVertexArray &vArray, std::uint64_t drawType) const
	{
		vArray.bind();
		
		if (vArray.getIndexCount() == 0u)
			AGL_CALL(glDrawArrays(drawType, 0u, vArray.getVertexCount()));
		else
			AGL_CALL(glDrawElements(drawType, vArray.getIndexCount(), GL_UNSIGNED_INT, 0u));
	}

	void CRenderer::addShader(std::uint32_t name, CShader &&shader)
	{
		AGL_CORE_ASSERT(shaders_.find(name) == shaders_.end(), "Shader already added!");

		shaders_[name] = std::move(shader);
	}

	const CShader& CRenderer::getShader(std::uint32_t name) const
	{
		AGL_CORE_ASSERT(shaders_.find(name) != shaders_.end(), "Shader does not exist!");

		return shaders_.at(name);
	}

	const CShader& CRenderer::getActiveShader() const
	{
		AGL_CORE_ASSERT(shaders_.find(active_) != shaders_.end(), "Shader does not exist!");

		return shaders_.at(active_);
	}

	void CRenderer::setActiveShader(std::uint32_t name)
	{
		AGL_CORE_ASSERT(shaders_.find(name) != shaders_.end(), "Shader does not exist!");

		active_ = name;
		shaders_.at(name).setActive();
	}

}