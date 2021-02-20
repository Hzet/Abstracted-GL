#include "directional-light-uniform.hpp"
#include "default-agl-shaders.hpp"

namespace agl
{
	void CDirectionalLight::setName(const std::string &name)
	{
		IUniform::setName(name);

		create(".direction", Shader::LIGHT_SHADER);
		create(".ambient", Shader::LIGHT_SHADER);
		create(".diffuse", Shader::LIGHT_SHADER);
		create(".specular", Shader::LIGHT_SHADER);
		create(".color", Shader::LIGHT_SHADER);
	}

	void CDirectionalLight::passToShader() const
	{
		passValue(".ambient", ambient);
		passValue(".diffuse", diffuse);
		passValue(".specular", specular);
		passValue(".direction", direction);
		passValue(".color", color);
	}

	std::unique_ptr<IUniform> CDirectionalLight::clone() const
	{
		return std::unique_ptr<IUniform>(new CDirectionalLight(*this));
	}
}

