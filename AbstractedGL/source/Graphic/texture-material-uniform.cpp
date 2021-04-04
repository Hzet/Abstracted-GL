#include "texture-material-uniform.hpp"
#include "default-agl-shaders.hpp"
#include "../System/gl-core.hpp"
#include "texture-atlas.hpp"

namespace agl
{
	static std::int32_t updateTexture(const std::vector<CTextureUID>& textures, std::uint32_t count, CUniformArray<CUniform<std::int32_t>> &bindings, std::int32_t textureOffset)
	{
		if (textures.size() != bindings.count())
		{
			bindings.resize(textures.size());
			count = bindings.count();
		}
		for (std::uint32_t i = 0u; i < bindings.count(); i++, textureOffset++)
		{
			AGL_CALL(glActiveTexture(GL_TEXTURE0 + textureOffset));
			CTextureAtlas::GetTexture(textures[i]).bind();
			bindings[i]() = textureOffset;
		}

		return textureOffset;
	}

	CTextureMaterial::CTextureMaterial(const std::string &name, IUniform const * const parent /*= nullptr*/)
		: IUniformPack(name, parent),
		ambientCount_("ambient_count", { ambientBindings_ }, { &CUniformArray<CUniform<std::int32_t>>::count }, this),
		ambientBindings_("ambient", this),
		specularCount_("specular_count", { specularBindings_ }, { &CUniformArray<CUniform<std::int32_t>>::count }, this),
		specularBindings_("specular", this),
		diffuseCount_("diffuse_count", { diffuseBindings_ }, { &CUniformArray<CUniform<std::int32_t>>::count }, this),
		diffuseBindings_("diffuse", this)
	{
		addUniforms();
	}

	CTextureMaterial::CTextureMaterial(CTextureMaterial &&other)
		: IUniformPack(other),
		ambient(other.ambient),
		ambientCount_(other.ambientCount_, { ambientBindings_ }),
		ambientBindings_(other.ambientBindings_),
		specular(other.specular),
		specularCount_(other.specularCount_, { specularBindings_ }),
		specularBindings_(other.specularBindings_),
		diffuse(other.diffuse),
		diffuseCount_(other.diffuseCount_, { diffuseBindings_ }),
		diffuseBindings_(other.diffuseBindings_)
	{
		addUniforms();
	}

	CTextureMaterial::CTextureMaterial(const CTextureMaterial &other)
		: IUniformPack(std::move(other)),
		ambient(std::move(other.ambient)),
		ambientBindings_(std::move(other.ambientBindings_)),
		ambientCount_(std::move(other.ambientCount_), { ambientBindings_ }),
		specular(std::move(other.specular)),
		specularBindings_(std::move(other.specularBindings_)),
		specularCount_(std::move(other.specularCount_), { specularBindings_ }),
		diffuse(std::move(other.diffuse)),
		diffuseBindings_(std::move(other.diffuseBindings_)),
		diffuseCount_(std::move(other.diffuseCount_), { diffuseBindings_ })
	{
		addUniforms();
	}

	bool CTextureMaterial::isEmpty() const
	{
		return specular.empty() && diffuse.empty() && ambient.empty();
	}

	void CTextureMaterial::passUniform() const
	{
		std::int32_t textureOffset = 0;

		textureOffset += updateTexture(ambient, ambientCount_, ambientBindings_, textureOffset);
		textureOffset += updateTexture(diffuse, diffuseCount_, diffuseBindings_, textureOffset);
		textureOffset += updateTexture(specular, specularCount_, specularBindings_, textureOffset);

		IUniformPack::passUniform();
	}

	std::unique_ptr<agl::IUniform> CTextureMaterial::clone() const
	{
		return std::unique_ptr<IUniform>(new CTextureMaterial(*this));
	}

	void CTextureMaterial::addUniforms()
	{
		addUniform(ambientCount_);
		addUniform(ambientBindings_);

		addUniform(specularCount_);
		addUniform(specularBindings_);

		addUniform(diffuseCount_);
		addUniform(diffuseBindings_);
	}

}