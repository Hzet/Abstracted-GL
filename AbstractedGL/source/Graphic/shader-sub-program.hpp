#pragma once 

#include <string>
#include <cstdint>

#include "../System/gl-object.hpp"

namespace agl
{
	class CShader;

	namespace graphics
	{
		/// <summary>
		/// A partial shader program.
		/// </summary>
		class CSubShader final
			: protected system::IGLObject
		{
		public:
			using system::IGLObject::IGLObject;

			/// <summary>
			/// Set 'type_' to zero.
			/// </summary>
			CSubShader();

			/// <summary>
			/// Default move constructor.
			/// </summary>
			/// <param name=""></param>
			CSubShader(CSubShader&&) = default;

			/// <summary>
			/// Destroy the partial program.
			/// </summary>
			~CSubShader();

			/// <summary>
			/// Default move assignment operator.
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			CSubShader& operator=(CSubShader&&) = default;

		private:
			friend class CShader;

			/// <summary>
			/// Get the object's id.
			/// </summary>
			/// <returns>
			/// The id
			/// </returns>
			std::uint32_t getID() const;

			/// <summary>
			/// Get the partial shader type.
			/// </summary>
			/// <returns>
			/// The type
			/// </returns>
			std::uint64_t getType() const;

			/// <summary>
			/// Set the 'source' code for a partial shader of given 'type'.
			/// </summary>
			/// <param name="type">The type</param>
			/// <param name="source">The source</param>
			/// <returns>
			/// True - source set successfully
			/// False - failure, no source code has been set
			/// </returns>
			bool setSource(const std::uint64_t type, const std::string &source);

			/// <summary>
			/// Loads the 'source' code for a partial shader of given 'type' from a file.
			/// </summary>
			/// <param name="type">The type</param>
			/// <param name="filename">The filepath</param>
			/// <returns>
			/// True - source set successfully
			/// False - failure, no source code has been set
			/// </returns>
			bool loadFromFile(const std::uint64_t type, const std::string &filename);

			/// <summary>
			/// Loads the 'source' code for a partial shader program from contiguous array of 'size'.
			/// The program is of 'type'.
			/// </summary>
			/// <param name="type">The type</param>
			/// <param name="source">The source</param>
			/// <param name="size">The size of 'source'</param>
			/// <returns></returns>
			bool loadFromMemory(const std::uint64_t type, const char *source, std::uint64_t size);

			/// <summary>
			/// Compile the partial shader program.
			/// If this method fails, it will be notified by AGL_CORE_ERROR.
			/// </summary>
			/// <returns>
			/// True - compilation succeed
			/// False - failure
			/// </returns>
			bool compile(); // may throw

			/// <summary>
			/// Generate the OpenGL's id.
			/// </summary>
			virtual void create() override;

			/// <summary>
			/// Delete the id and set it to zero.
			/// </summary>
			virtual void destroy() override;

			std::uint64_t type_;
			std::string source_;
		};
	}
}