#pragma once
#include <cstdint>

#include "agl/system/glcore/destructive-move.hpp"

namespace agl
{
	/// <summary>
	/// An interface providing basic OpenGL object' functionality.
	/// The instance has it's own ID visible in derived classes.
	/// If the 'm_id_object' is equal to zero, the object is considered to be in invalid state - it is not registered.
	/// </summary>
	class gl_object
		: public destructive_move
	{
	public:
		using destructive_move::destructive_move;

		/// <summary>
		/// Set the id to 0.
		/// </summary>
		gl_object();

		/// <summary>
		/// Check whether this object's status is active.
		/// </summary>
		/// <returns>
		/// True - object is a valid OpenGL object
		/// False - object is not a valid OpenGL object
		/// </returns>
		bool is_created() const;

		/// <summary>
		/// uniform_register the object as an OpenGL object.
		/// </summary>
		virtual void create() = 0;

		/// <summary>
		/// Unregister the object.
		/// </summary>
		virtual void destroy() = 0;

		/// <summary>
		/// Bind the object to current OpenGL context.
		/// </summary>
		virtual void bind() const {};

		/// <summary>
		/// Unbind the object.
		/// </summary>
		virtual void unbind() const {};

	protected:
		std::uint32_t m_id_object;
	};
}