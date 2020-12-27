#pragma once

#include "../System/gl-object.hpp"

namespace agl
{
	class CIndexBuffer final
		: public system::IGLObject
	{
	public:
		using system::IGLObject::IGLObject;

		/// <summary>
		/// Set the object's state to invalid.
		/// </summary>
		CIndexBuffer();
		
		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		CIndexBuffer(CIndexBuffer&&) = default;


		/// <summary>
		/// Destroy the object.
		/// </summary>
		~CIndexBuffer();

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CIndexBuffer& operator=(CIndexBuffer&&) = default;

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
		/// Call OpenGL to allocate 'sizeof(uint32_t) * count' bytes of memory for 'count' objects and insert 'data'.
		/// </summary>
		/// <param name="data">The data</param>
		/// <param name="count">The count</param>
		void allocate(std::uint32_t const * const data, std::uint32_t count);

		/// <summary>
		/// Call OpenGL to insert 'data' of 'sizeof(uint32_t) * count' bytes in the buffer's memory at 'sizeof(uint32_t) * offset'.
		/// </summary>
		/// <param name="data">The data</param>
		/// <param name="offset">The offset in elements</param>
		/// <param name="count">The count</param>
		void buffer(std::uint32_t const * const data, std::uint32_t offset, std::uint32_t count);

		/// <summary>
		/// Get the count of the elements.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::uint32_t getCount() const;

	private:
		std::uint32_t count_;
	};
}