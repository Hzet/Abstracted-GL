#pragma once

#include <cstdint>
#include <string>

#include "../System/gl-object.hpp"

namespace agl
{
	/// <summary>
	/// The base class for texture providing IGLObject implementation
	/// and general texture specific methods.
	/// </summary>
	class ITexture
		: public system::IGLObject
	{
	public:
		using system::IGLObject::IGLObject;

		ITexture() = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~ITexture();

		/// <summary>
		/// Set the texture parameter.
		/// The texture must be first bound in the current context.
		/// </summary>
		/// <param name="setting">OpenGL texture setting enumn</param>
		/// <param name="value">Value related to the 'setting'</param>
		void setParameter(const std::uint64_t setting, const std::uint64_t value) const;

		/// <summary>
		/// Register OpenGL object.
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
		virtual std::uint64_t getTarget() const = 0;
	};
}