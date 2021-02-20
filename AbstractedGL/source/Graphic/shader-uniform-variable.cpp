#include "shader-uniform-variable.hpp"

namespace agl
{
	void IUniformVariable::setName(const std::string &name)
	{
		reset();
		IUniform::setName(name);
	}

	void IUniformVariable::create(const std::string &name, const CShaderUID &shaderUID)
	{
		uniformManager_.create(getName() + name, shaderUID);
	}

	const CShaderUID& IUniformVariable::getShaderOf(const std::string &name)
	{
		return uniformManager_.getShaderOf(getName() + name);
	}

	void IUniformVariable::redirect(const std::string &name, const CShaderUID &shaderUID)
	{
		uniformManager_.redirect(getName() + name, shaderUID);
	}

	void IUniformVariable::reset()
	{
		uniformManager_.reset();
	}

}