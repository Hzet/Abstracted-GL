#pragma once 

#include "texture-base.hpp"
#include "texture-uid.hpp"
#include "shader-uniform-pack.hpp"
#include "shader-uniform-array.hpp"
#include "shader-uniform-variable.hpp"

namespace agl
{
	class CTextureMaterial
		: public IUniformPack
	{
	public:
		CTextureMaterial(const std::string &name, IUniform const * const parent = nullptr);

		CTextureMaterial(CTextureMaterial &&other);
		CTextureMaterial(const CTextureMaterial &other);

		CTextureMaterial& operator=(CTextureMaterial &&other) = default;
		CTextureMaterial& operator=(const CTextureMaterial &other) = default;

		bool isEmpty() const;

		virtual void passUniform() const override;

		virtual std::unique_ptr<IUniform> clone() const override;

		std::vector<CTextureUID> ambient;
		std::vector<CTextureUID> diffuse;
		std::vector<CTextureUID> specular;

	private:
		using BindUniform = CUniformArray<CUniform<std::int32_t>>;
		using CountUniform = CUniform<std::int32_t, const CUniformArray<CUniform<std::int32_t>>&, std::uint64_t(CUniformArray<CUniform<std::int32_t>>::*)()const>;

		void addUniforms();

		mutable BindUniform ambientBindings_;
		mutable CountUniform ambientCount_;

		mutable BindUniform diffuseBindings_;
		mutable CountUniform diffuseCount_;

		mutable BindUniform specularBindings_;
		mutable CountUniform specularCount_;
	};
}