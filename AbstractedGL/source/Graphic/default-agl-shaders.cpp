#include "default-agl-shaders.hpp"
#include "shader-manager.hpp"
#include "shader-uid.hpp"

namespace agl
{
	namespace Shader
	{
		const CShaderUID BASIC_SHADER;
		const CShaderUID LIGHT_SHADER;
	}

	static const CShaderManager BASIC_SHADER = { Shader::BASIC_SHADER, CShader::LoadFromFile("resource\\basic.vsh", "resource\\basic.fsh") };
	static const CShaderManager LIGHT_SHADER = { Shader::LIGHT_SHADER, CShader::LoadFromFile("resource\\light.vsh", "resource\\light.fsh") };
}

