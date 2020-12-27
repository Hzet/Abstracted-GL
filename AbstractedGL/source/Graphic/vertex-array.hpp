#pragma once

#include "vertex-buffer.hpp"
#include "vertex-layout.hpp"
#include "index-buffer.hpp"

namespace agl
{
	/// <summary>
	/// OpenGL vertex array abstraction.
	/// </summary>
	class CVertexArray final
		: public system::IGLObject
	{
	public:
		using system::IGLObject::IGLObject;

		/// <summary>
		/// Set the object's state to invalid.
		/// </summary>
		CVertexArray();
		
		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		CVertexArray(CVertexArray&&) = default;

		/// <summary>
		/// Destroy the object.
		/// </summary>
		~CVertexArray();

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CVertexArray& operator=(CVertexArray&&) = default;

		/// <summary>
		/// Bind OpenGL object to the current context.
		/// </summary>
		virtual void bind() const override;

		/// <summary>
		/// Unbind OpenGL object.
		/// </summary>
		virtual void unbind() const override;
		 
		/// <summary>
		/// Create OpenGL object.
		/// </summary>
		virtual void create() override;

		/// <summary>
		/// Delete OpenGL object and reset it to invalid state.
		/// </summary>
		virtual void destroy() override;

		/// <summary>
		/// Set the vertex buffer and it's vertex layout.
		/// </summary>
		/// <param name="buffer">The buffer</param>
		/// <param name="layout">The buffer's layout</param>
		void setBuffer(const CVertexBuffer &buffer, const CVertexLayout &layout);

		/// <summary>
		/// Set the vertex buffer and it's layout and draw elements in order provided in index buffer.
		/// </summary>
		/// <param name="vBuffer">The buffer</param>
		/// <param name="layout">The buffer's layout</param>
		/// <param name="iBuffer">The index buffer</param>
		void setBuffer(const CVertexBuffer &vBuffer, const CVertexLayout &layout, const CIndexBuffer &iBuffer);

		/// <summary>
		/// Get the count of indices.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::uint32_t getIndexCount() const;

		/// <summary>
		/// Get the count of vertices.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::uint32_t getVertexCount() const;

	private:
		std::uint32_t iCount_;
		std::uint32_t vCount_;
	};
}