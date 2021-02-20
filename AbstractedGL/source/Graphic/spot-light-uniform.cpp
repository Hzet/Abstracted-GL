#include "spot-light-uniform.hpp"

namespace agl
{
	void CSpotLight::setName(const std::string &name)
	{
		IUniform::setName(name);

		create(".ambient", Shader::LIGHT_SHADER);
		create(".diffuse", Shader::LIGHT_SHADER);
		create(".specular", Shader::LIGHT_SHADER);
		create(".range", Shader::LIGHT_SHADER);
		create(".cutOff", Shader::LIGHT_SHADER);
		create(".direction", Shader::LIGHT_SHADER);
		create(".position", Shader::LIGHT_SHADER);
		create(".color", Shader::LIGHT_SHADER);
	}

	void CSpotLight::passToShader() const
	{
		passValue(".ambient", ambient);
		passValue(".diffuse", diffuse);
		passValue(".specular", specular);
		passValue(".range", range);
		passValue(".cutOff", cutOff);
		passValue(".direction", direction);
		passValue(".color", color);
	}

	std::unique_ptr<IUniform> CSpotLight::clone() const
	{
		return std::unique_ptr<IUniform>(new CSpotLight(*this));
	}
}

