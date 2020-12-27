#pragma once 

#include "assert.hpp"

#include <glad/glad.h>

#ifdef AGL_DEBUG
	namespace agl
	{
		namespace system
		{
			/// <summary>
			/// Read OpenGL error until it is GL_NO_ERROR
			/// </summary>
			void GLClearError();

			/// <summary>
			/// Check whether the value represents an error
			/// </summary>
			/// <returns>
			/// True - value is not an error
			/// False - value represents an error
			/// </returns>
			bool GLCheckError(std::uint64_t value);

			/// <summary>
			/// Get the value of an error if such has occurred.
			/// </summary>
			/// <returns>
			/// Last error value
			/// </returns>
			std::uint64_t GLGetLastError();
		}
	}

	/// <summary>
	/// Simplified define to put OpenGL call in. 
	/// Asserts on call failure.
	/// </summary>
	#define AGL_CALL(call) \
		do { \
			::agl::system::GLClearError(); \
			call; \
			AGL_CORE_ASSERT(::agl::system::GLCheckError(::agl::system::GLGetLastError()), "Failed to execute OpenGL call!\n", "Error code: [", ::agl::system::GLGetLastError(), "]\n"); \
		} while(false)
#else
	#define AGL_CALL(call) call
#endif