#pragma once

#include <cstdint>
#include <string>

#include "../System/gl-object.hpp"

namespace agl
{
	namespace graphics
	{
		/// <summary>
		/// The base class for texture providing IGLObject implementation
		/// and general texture specific methods.
		/// </summary>
		class CTextureBase
			: public system::IGLObject
		{
		public:
			using system::IGLObject::IGLObject;

			/// <summary>
			/// Create the texture of type 'target'.
			/// </summary>
			/// <param name="target">OpenGL texture target enum</param>
			CTextureBase(const std::uint64_t target);

			/// <summary>
			/// Default move constructor.
			/// </summary>
			/// <param name=""></param>
			CTextureBase(CTextureBase&&) = default;

			/// <summary>
			/// Default virtual destructor.
			/// </summary>
			virtual ~CTextureBase();

			/// <summary>
			/// Default move assignment operator.
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			CTextureBase& operator=(CTextureBase&&) = default;

			/// <summary>
			/// Set the texture parameter.
			/// The texture must be first bound in the current context.
			/// </summary>
			/// <param name="setting">OpenGL texture setting enumn</param>
			/// <param name="value">Value related to the 'setting'</param>
			void setParameter(const std::uint64_t setting, const std::uint64_t value) const;

			/// <summary>
			/// Get the texture's target.
			/// </summary>
			/// <returns>
			/// OpenGL texture target enum
			/// </returns>
			std::uint64_t getTarget() const;

			/// <summary>
			/// Get the number of this texture slot.
			/// </summary>
			/// <returns></returns>
			std::uint32_t getSlotNumber() const;


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
			/// Interface for loading the texture from a file.
			/// </summary>
			/// <param name="filename">The filepath</param>
			/// <returns>
			/// True - texture loaded successfully
			/// False - texture has not been loaded
			/// </returns>
			virtual bool loadFromFile(const std::string &filename) = 0;

		private:
			const std::uint64_t target_;
			std::uint32_t textureSlot_;
		};
	}
}