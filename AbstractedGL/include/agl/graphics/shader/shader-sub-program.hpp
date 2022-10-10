#pragma once 
#include <string>
#include <cstdint>

#include "graphics/shader/shader-type.hpp"
#include "system/glcore/gl-object.hpp"

namespace agl
{
	class shader;

	/// <summary>
	/// A partial s program.
	/// </summary>
	class sub_shader final
		: protected gl_object
	{
	public:
		using gl_object::gl_object;

		/// <summary>
		/// Set 'm_type' to zero.
		/// </summary>
		sub_shader();

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		sub_shader(sub_shader&&) = default;

		/// <summary>
		/// Destroy the partial program.
		/// </summary>
		~sub_shader();

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		sub_shader& operator=(sub_shader&&) = default;

	private:
		friend class shader;

		/// <summary>
		/// Get the object's id.
		/// </summary>
		/// <returns>
		/// The id
		/// </returns>
		std::uint32_t get_id() const;

		/// <summary>
		/// Get the partial s type.
		/// </summary>
		/// <returns>
		/// The type
		/// </returns>
		shader_type get_type() const;

		/// <summary>
		/// Set the 'source' code for a partial s of given 'type'.
		/// </summary>
		/// <param name="type">The type</param>
		/// <param name="source">The source</param>
		/// <returns>
		/// True - source set successfully
		/// False - failure, no source code has been set
		/// </returns>
		bool set_source(shader_type type, const std::string &source);

		/// <summary>
		/// Loads the 'source' code for a partial s of given 'type' from a file.
		/// </summary>
		/// <param name="type">The type</param>
		/// <param name="filename">The filepath</param>
		/// <returns>
		/// True - source set successfully
		/// False - failure, no source code has been set
		/// </returns>
		bool load_from_file(shader_type type, const std::string &filename);

		/// <summary>
		/// Loads the 'source' code for a partial s program from contiguous array of 'size'.
		/// The program is of 'type'.
		/// </summary>
		/// <param name="type">The type</param>
		/// <param name="source">The source</param>
		/// <param name="size">The size of 'source'</param>
		/// <returns></returns>
		bool load_from_memory(shader_type type, const char *source, std::uint64_t size);

		/// <summary>
		/// Compile the partial s program.
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

		shader_type m_type;
		std::string m_source;
	};
}