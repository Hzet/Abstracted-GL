#pragma once
#include "graphics/render/index-buffer.hpp"
#include "graphics/render/vertex-buffer.hpp"
#include "graphics/render/vertex-layout.hpp"

namespace agl
{
	/// <summary>
	/// OpenGL vertex array abstraction.
	/// </summary>
	class vertex_array final
		: public gl_object
	{
	public:
		using gl_object::gl_object;

		/// <summary>
		/// Set the object's state to invalid.
		/// </summary>
		vertex_array();
		
		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		vertex_array(vertex_array&&) = default;

		/// <summary>
		/// Destroy the object.
		/// </summary>
		~vertex_array();

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		vertex_array& operator=(vertex_array&&) = default;

		/// <summary>
		/// Bind OpenGL object to the current context.
		/// </summary>
		virtual void bind() const override;

		/// <summary>
		/// Unbind OpenGL object.
		/// </summary>
		virtual void unbind() const override;
		 
		/// <summary>
		/// create OpenGL object.
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
		void set_buffer(const vertex_buffer &buffer, const vertex_layout &layout);

		/// <summary>
		/// Set the vertex buffer and it's layout and draw elements in order provided in index buffer.
		/// </summary>
		/// <param name="vBuffer">The buffer</param>
		/// <param name="layout">The buffer's layout</param>
		/// <param name="iBuffer">The index buffer</param>
		void set_buffer(const vertex_buffer &vBuffer, const vertex_layout &layout, const index_buffer &iBuffer);

		/// <summary>
		/// Get the count of indices.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::uint32_t get_index_count() const;

		/// <summary>
		/// Get the count of vertices.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::uint32_t get_vertex_count() const;

	private:
		std::uint32_t m_icount;
		std::uint32_t m_vcount;
	};
}