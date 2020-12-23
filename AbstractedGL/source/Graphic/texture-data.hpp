#pragma once 

#include "shader-data.hpp"

namespace agl
{
	class CTextureData
		: public IShaderData
	{
	public:
		CTextureData() = default;
		CTextureData(CTextureData&&) = default;
		CTextureData(const CTextureData&) = default;
		CTextureData(const std::uint32_t d, std::uint32_t spec, const float s);

		CTextureData& operator=(CTextureData&&) = default;
		CTextureData& operator=(const CTextureData&) = default;

		float shininess;
		std::uint32_t diffuse;
		std::uint32_t specular;

	protected:		
		virtual void setData(const std::string &name, const CShader &shader) const override;

		std::unique_ptr<IShaderData> clone() const override;
	};
}