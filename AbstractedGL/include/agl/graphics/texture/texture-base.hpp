#pragma once
#include <cstdint>
#include <string>

#include "agl/graphics/texture/texture-type.hpp"
#include "agl/system/glcore/gl-object.hpp"

namespace agl
{
	/// <summary>
	/// The base class for texture providing gl_object implementation
	/// and general texture specific methods.
	/// </summary>
	class texture_base
		: public gl_object
	{
	public:
		using gl_object::gl_object;

		texture_base() = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~texture_base();

		/// <summary>
		/// Set the texture parameter.
		/// The texture must be first bound in the current context.
		/// </summary>
		/// <param name="setting">OpenGL texture setting enumn</param>
		/// <param name="value">value related to the 'setting'</param>
		void set_parameter(const std::uint64_t setting, const std::uint64_t value) const;

		/// <summary>
		/// uniform_register OpenGL object.
		/// </summary>
		virtual void create() override;
			
		/// <summary>
		/// Unregister the OpenGL object and clear resources.
		/// </summary>
		virtual void destroy() override;

		/// <summary>
		/// Bind OpenGL object.
		/// </summary>
		virtual void bind() const override;

		/// <summary>
		/// Unbind OpenGL object.
		/// </summary>
		virtual void unbind() const override;

		/// <summary>
		/// Pure virtual method to get the texture's target.
		/// </summary>
		/// <returns>
		/// OpenGL texture target enum
		/// </returns>
		virtual texture_type get_target() const = 0;
	};
}