#include "light-point-entry.hpp"

namespace agl
{
	void CLightPointEntry::setName(const std::string &name)
	{
		IShaderEntry::setName(name);

		attachEntry("ambient", Shader::LIGHT_SHADER);
		attachEntry("diffuse", Shader::LIGHT_SHADER);
		attachEntry("specular", Shader::LIGHT_SHADER);
		attachEntry("range", Shader::LIGHT_SHADER);
		attachEntry("cutOff", Shader::LIGHT_SHADER);
		attachEntry("direction", Shader::LIGHT_SHADER);
		attachEntry("position", Shader::LIGHT_SHADER);
		attachEntry("color", Shader::LIGHT_SHADER);
	}

	void CLightPointEntry::passToShader() const
	{
		passEntry("ambient", ambient);
		passEntry("diffuse", diffuse);
		passEntry("specular", specular);
		passEntry("range", range);
		passEntry("cutOff", cutOff);
		passEntry("direction", direction);
		passEntry("color", color);
	}

	std::unique_ptr<IShaderEntry> CLightPointEntry::clone() const
	{
		return std::unique_ptr<IShaderEntry>(new CLightPointEntry(*this));
	}
}

