#pragma once

#include "drawable.hpp"
#include "transformable.hpp"
#include "vertex-array.hpp"
#include "renderer.hpp"
#include "shader-uniform-manager.hpp"
#include "shader-uniform-vector.hpp"
#include "../System/tuple-buffer.hpp"

namespace agl
{
	template <class... Args>
	class CMesh
		: public IDrawable,
		public CTransformable
	{
	public:
		CMesh();
		CMesh(CMesh&&) = default;
		CMesh(const CMesh&) = default;
		virtual ~CMesh() = default;

		void addVertex(Args&&... args);
		template <std::uint64_t I> auto& getVertexAttribute(const std::uint64_t index);
		template <std::uint64_t I> const auto& getVertexAttribute(const std::uint64_t index) const;

		void setVertices(const CTupleBuffer<Args...> &vertices);
		template <std::size_t I, class T> void setVertices(const std::vector<T> &vertices);
		template <std::size_t I, class T> void setVertices(T const * const vertices, const std::uint64_t count);

		void setIndices(const std::vector<std::uint32_t> &indices);
		void setIndices(std::uint32_t const * const indices, const std::uint64_t count);

		std::uint64_t getDrawType() const;
		void setDrawType(const std::uint64_t drawType);

		const CShaderUID& getShader() const;
		void setShader(const CShaderUID &uid);

		CUniformVector& getUniforms() const;
		void addUniform(const IUniform &uniform);
		void setUniforms(const CUniformVector &shaderEntries);

		const CUniformManager& getUniformManager() const;
		void redirectUniform(const std::string &name, const CShaderUID &shaderUID);

		virtual void draw(const CRenderer &renderer) const override;

	private:
		static CVertexLayout GetLayout();
		template <std::size_t I = 0> static void GetLayout_impl(CVertexLayout &result);

		static const CVertexLayout Layout_;

		void updateIBuffer() const;
		void updateVBuffer() const;
		void updateVArray() const;

		mutable bool vbUpdate_;
		mutable bool ibUpdate_;

		mutable CVertexBuffer vBuffer_;
		mutable CIndexBuffer iBuffer_;
		mutable CVertexArray vArray_;

		CShaderUID myShader_;

	protected:
		CUniformManager uniformManager_;
	private:
		CUniformVector uniforms_;

		std::uint64_t drawType_;
		CTupleBuffer<Args...> vertices_;
		std::vector<std::uint32_t> indices_;
	};

#include "mesh.inl"
}