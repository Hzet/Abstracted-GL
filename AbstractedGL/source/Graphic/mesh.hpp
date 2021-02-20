#pragma once

#include "vertex-object.hpp"
#include "shader-uniform-manager.hpp"
#include "shader-uniform-vector.hpp"

namespace agl
{
	template <class... Args>
	class CMesh
		: public graphics::CVertexObject<Args...>
	{
	public:
		CMesh();
		
		const CShaderUID& getShader() const;
		void setShader(const CShaderUID &uid);

		CUniformVector& getUniforms() const;
		void addUniform(const IUniform &uniform);
		void setUniforms(const CUniformVector &shaderEntries);

		const CUniformManager& getUniformManager() const;
		void redirectUniform(const std::string &name, const CShaderUID &shaderUID);

		virtual void draw(const CRenderer &renderer) const override;

	protected:
		CUniformManager uniformManager_;

	private:
		CShaderUID myShader_;
		CUniformVector uniforms_;
	};

#include "mesh.inl"
}