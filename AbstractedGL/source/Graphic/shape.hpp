#pragma once

#include "drawable.hpp"
#include "transformable.hpp"
#include "vertex-array.hpp"
#include "../System/tuple-buffer.hpp"

namespace agl
{
	template <class... Args>
	class CShape
		: public IDrawable,
		public CTransformable
	{
	public:
		void setVertices(const CTupleBuffer<Args...> &vertices);
		
		template <std::size_t I, class T> void setVertices(const std::vector<T> &vertices);
		template <std::size_t I, class T> void setVertices(T const * const vertices, std::uint64_t count);

		void setIndices(const std::vector<std::uint32_t> &indices);
		void setIndices(std::uint32_t const * const indices, std::uint64_t count);

		void setDrawType(const std::uint64_t drawType);
		std::uint64_t getDrawType() const;

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

		std::uint64_t drawType_;
		CTupleBuffer<Args...> vertices_;
		std::vector<std::uint32_t> indices_;
	};


#include "shape.inl"
}