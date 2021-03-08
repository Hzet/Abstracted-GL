#include "shader-uniform-pack.hpp"

namespace agl
{
	IUniformPack::IUniformPack(IUniformPack &&other)
		: IUniform(std::move(other))
	{
	}

	IUniformPack::IUniformPack(const IUniformPack &other)
		: IUniform(other)
	{
	}

	IUniformPack::IUniformPack(const IUniformPack &other, IUniform const * const parent)
		: IUniform(other, parent)
	{
	}

	void IUniformPack::addUniform(IUniform &uniform)
	{
		uniform.updateNamespace(getFullName());
		uniforms_.push_back(&uniform);
	}

	void IUniformPack::passUniform() const
	{
		for (const auto &v : uniforms_)
			v->passUniform();
	}

	void IUniformPack::setIndex(std::uint64_t index)
	{
		IUniform::setIndex(index);

		for (auto &v : uniforms_)
			v->updateNamespace(getFullName());
	}


	void IUniformPack::setShader(const CShaderUID &shaderUID)
	{
		for (auto &v : uniforms_)
			v->setShader(shaderUID);
	}

	void IUniformPack::updateNamespace(const std::string &name)
	{
		IUniform::updateNamespace(name);

		for (auto &v : uniforms_)
			v->updateNamespace(getFullName());
	}
}