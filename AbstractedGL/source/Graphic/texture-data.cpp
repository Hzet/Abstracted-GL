#include "texture-data.hpp"
#include "shader-program.hpp"

namespace agl
{
	CTextureData::CTextureData(const std::uint32_t d, std::uint32_t spec, const float s)
		: shininess(s),
		diffuse(d),
		specular(spec)
	{
	}

	std::unique_ptr<IShaderData> CTextureData::clone() const
	{
		return std::unique_ptr<IShaderData>(new CTextureData(*this));
	}

	void CTextureData::setData(const std::string &name, const CShader &shader) const
	{
		shader.setInt(name + ".diffuse", diffuse);
		shader.setInt(name + ".specular", specular);
		shader.setFloat(name + ".shininess", shininess);
	}
}

