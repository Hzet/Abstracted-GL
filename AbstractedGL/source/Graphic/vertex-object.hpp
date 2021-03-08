#pragma once

#include "drawable.hpp"
#include "transformable.hpp"
#include "vertex-array.hpp"
#include "renderer.hpp"
#include "../System/tuple-buffer.hpp"

namespace agl
{
	namespace graphics
	{
		/// <summary>
		/// An object that can be represented graphically. It has it's transform and is capable of storing vertices and indices.
		/// </summary>
		template <class... Args>
		class CVertexObject
			: public IDrawable,
			public CTransformable
		{
		public:
			/// <summary>
			/// Default constructor.
			/// </summary>
			CVertexObject() = default;

			/// <summary>
			/// Move constructor.
			/// </summary>
			/// <param name="other">The other object</param>
			CVertexObject(CVertexObject &&other);

			/// <summary>
			/// Copy constructor.
			/// </summary>
			/// <param name="other">The other object</param>
			CVertexObject(const CVertexObject &other);

			/// <summary>
			/// Default move assignment operator.
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			CVertexObject& operator=(CVertexObject &&other) = default;

			/// <summary>
			/// Default move assignment operator.
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			CVertexObject& operator=(const CVertexObject &other) = default;

			/// <summary>
			/// Default virtual constructor.
			/// </summary>
			virtual ~CVertexObject() = default;

			/// <summary>
			/// Adds a stride of data to the vertices.
			/// </summary>
			/// <param name="...args">The stride</param>
			void addVertex(Args&&... args);

			/// <summary>
			/// Returns the attribute from 'I'th type index residing at 'index' position.
			/// </summary>
			/// <param name="index">The index</param>
			/// <returns>The attribute</returns>
			template <std::uint64_t I> auto& getVertexAttribute(const std::uint64_t index);

			/// <summary>
			/// Returns the attribute from 'I'th type index residing at 'index' position.
			/// </summary>
			/// <param name="index">The index</param>
			/// <returns>The attribute</returns>
			template <std::uint64_t I> const auto& getVertexAttribute(const std::uint64_t index) const;

			/// <summary>
			/// Sets the vertices from a tuple buffer.
			/// </summary>
			/// <param name="vertices">The buffer</param>
			void setVertices(const CTupleBuffer<Args...> &vertices);

			/// <summary>
			/// Sets the vertex attributes at 'I'th type index to contain 'vertices'.
			/// The underlying tuple buffer count will be expanded if required, 
			/// but will not shrink if count of elements in 'vertices' is less than this object'.
			/// </summary>
			/// <param name="vertices">The vertices</param>
			template <std::size_t I, class T> void setVertices(const std::vector<T> &vertices);

			/// <summary>
			/// Sets the vertex attributes at 'I'th type index to contain 'vertices'.
			/// The underlying tuple buffer count will be expanded if required, 
			/// but will not shrink if count of elements in 'vertices' is less than this object'.
			/// </summary>
			/// <param name="vertices">The vertices</param>
			/// <param name="count">The count of the elements</param>
			template <std::size_t I, class T> void setVertices(T const * const vertices, const std::uint64_t count);

			/// <summary>
			/// Sets the indices.
			/// </summary>
			/// <param name="indices">The indices</param>
			void setIndices(const std::vector<std::uint32_t> &indices);

			/// <summary>
			/// Sets the indices.
			/// </summary>
			/// <param name="indices">The indices</param>
			/// <param name="count">The count of the elements</param>
			void setIndices(std::uint32_t const * const indices, const std::uint64_t count);

			/// <summary>
			/// Returns the assigned draw type.
			/// </summary>
			/// <returns>The draw type</returns>
			std::uint64_t getDrawType() const;

			/// <summary>
			/// Sets the draw type.
			/// </summary>
			/// <param name="drawType">The draw type</param>
			void setDrawType(const std::uint64_t drawType);

			/// <summary>
			/// If necessary, update the buffers and then draw the entity.
			/// </summary>
			/// <param name="renderer">The renderer</param>
			virtual void draw(const CRenderer &renderer) const override;

		private:
			/// <summary>
			/// Returns the layout for this object.
			/// </summary>
			/// <returns>The layout</returns>
			static CVertexLayout GetLayout();

			/// <summary>
			/// Helper method. Pushes the 'I'th type layout.
			/// Works recursively.
			/// </summary>
			/// <param name="result">The layout</param>
			template <std::size_t I = 0> static void GetLayout_impl(CVertexLayout &result);

			static const CVertexLayout Layout_;

			/// <summary>
			/// Updates the index buffer.
			/// </summary>
			void updateIBuffer() const;

			/// <summary>
			/// Updates the vertex buffer.
			/// </summary>
			void updateVBuffer() const;

			/// <summary>
			/// Updates the vertex array.
			/// </summary>
			void updateVArray() const;

			std::uint64_t drawType_;
			CTupleBuffer<Args...> vertices_;
			std::vector<std::uint32_t> indices_;

			mutable bool vbUpdate_;
			mutable bool ibUpdate_;

			mutable CVertexBuffer vBuffer_;
			mutable CIndexBuffer iBuffer_;
			mutable CVertexArray vArray_;
		};

#include "vertex-object.inl"
	}
}