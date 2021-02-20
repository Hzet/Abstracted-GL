#include "shader-uniform-object.hpp"

namespace agl
{
	CUniformObject::CUniformObject()
		: shaderUID_(CShaderUID::InvalidValue())
	{
	}

/*
	void CUniformObject::redirectEntry(const std::string &name, const CShaderUID &shaderUID)
	{
		entriesManager_.redirectEntry(name, shaderUID);
	}
*/

	void CUniformObject::redirect(const CShaderUID &shaderUID)
	{
		shaderUID_ = shaderUID;
	}

	void CUniformObject::reset()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void CUniformObject::create(const std::string &name, const CShaderUID &shaderUID)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void CUniformObject::setName(const std::string &name)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void CUniformObject::passToShader() const
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	std::unique_ptr<agl::IUniform> CUniformObject::clone() const
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}