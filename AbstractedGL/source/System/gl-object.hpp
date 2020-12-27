#pragma once

#include <cstdint>
#include "move-only.hpp"

namespace agl
{
	namespace system
	{
		/// <summary>
		/// An interface providing basic OpenGL object' functionality.
		/// The instance has it's own ID visible in derived classes.
		/// If the 'objectID_' is equal to zero, the object is considered to be in invalid state - it is not registered.
		/// </summary>
		class IGLObject
			: public CMoveOnly
		{
		public:
			using CMoveOnly::CMoveOnly;

			/// <summary>
			/// Set the id to 0.
			/// </summary>
			IGLObject();

			/// <summary>
			/// Default move constructor.
			/// </summary>
			/// <param name=""></param>
			IGLObject(IGLObject&&) = default;

			/// <summary>
			/// Default virtual constructor.
			/// </summary>
			virtual ~IGLObject() = default;

			/// <summary>
			/// Default move assignment operator.
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			IGLObject& operator=(IGLObject&&) = default;

			/// <summary>
			/// Check whether this object's status is active.
			/// </summary>
			/// <returns>
			/// True - object is a valid OpenGL object
			/// False - object is not a valid OpenGL object
			/// </returns>
			bool isCreated() const;

			/// <summary>
			/// Register the object as an OpenGL object.
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
			std::uint32_t objectID_;
		};
	}
}