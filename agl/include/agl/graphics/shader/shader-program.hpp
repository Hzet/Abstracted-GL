#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "agl/graphics/shader/shader-sub-program.hpp"
#include "agl/graphics/shader/shader-uid.hpp"
#include "agl/system/glcore/gl-core.hpp"
#include "agl/system/glcore/destructive-move.hpp"

namespace agl
{
	class IShaderData;

	/// <summary>
	/// The class representing s program that consists of at least 2 partial s programs: GL_VERTEX_SHADER and GL_FRAGMENT_SHADER.
	/// </summary>
	class shader
		: private destructive_move
	{
	public:
		using destructive_move::destructive_move;

		/// <summary>
		/// Set s bits to zero.
		/// </summary>
		shader();

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		shader(shader&&) = default;

		/// <summary>
		/// Destroy the s program.
		/// </summary>
		~shader();

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		shader& operator=(shader&&) = default;

		void load_from_file(const std::string &vertex, const std::string &fragment, const std::string &geometry = "", const std::string &tessControl = "", const std::string &tessEvaluation = "", const std::string &compute = "");
		void load_from_source(const std::string &vertex, const std::string &fragment, const std::string &geometry = "", const std::string &tessControl = "", const std::string &tessEvaluation = "", const std::string &compute = "");

		/// <summary>
		/// Set the partial s program's 'source' from a string.
		/// </summary>
		/// <param name="type">The type</param>
		/// <param name="source">The source</param>
		/// <returns>
		/// True - success
		/// False - failure, no partial s has been attached
		/// </returns>
		bool attach_from_source(shader_type type, const std::string &source);

		/// <summary>
		/// Loads the partial s program's source from a file.
		/// </summary>
		/// <param name="type">The type</param>
		/// <param name="filename">The filename</param>
		/// <returns>
		/// True - success
		/// False - failure, no partial s has been attached</returns>
		bool attach_from_file(shader_type type, const std::string &filename);

		/// <summary>
		/// Loads the 'source' code for a partial s program from contiguous array of 'size'.
		/// The partial program is of 'type'.
		/// </summary>
		/// <param name="type"></param>
		/// <param name="data"></param>
		/// <param name="size"></param>
		/// <returns></returns>
		bool attach_from_memory(shader_type type, const char *data, std::uint64_t size);

		/// <summary>
		/// create and link the partial s programs together into a single s program object.
		/// Reports about encountered errors.
		/// </summary>
		/// <returns>
		/// True - linking successful
		/// False - linking failed
		/// </returns>
		bool link();

		/// <summary>
		/// Check whether this object's status is active.
		/// </summary>
		/// <returns>
		/// True - object is a valid OpenGL object
		/// False - object is not a valid OpenGL object
		/// </returns>
		bool is_created() const;

		/// <summary>
		/// Check whether the 'bit' partial s program is a part of this s program.
		/// </summary>
		/// <param name="bit">OpenGL enum for s bits</param>
		/// <returns>
		/// True - partial program is attached
		/// False - partial program is not attached
		/// </returns>
		bool has_shader(std::uint64_t bit) const;

		shader_uid get_shader_uid() const;

		/// <summary>
		/// Assign 'value' to a float u named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void set_uniform(std::int32_t location, const float value) const;

		/// <summary>
		/// Assign 'value' to a std::int32_t u named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void set_uniform(std::int32_t location, const std::int32_t value) const;

		/// <summary>
		/// Assign 'value' to a std::uint32_t u named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void set_uniform(std::int32_t location, const std::uint32_t value) const;

		/// <summary>
		/// Assign 'value' to a glm::vec2 u named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void set_uniform(std::int32_t location, const glm::vec2 &value) const;

		/// <summary>
		/// Assign 'value' to a glm::vec3 u named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void set_uniform(std::int32_t location, const glm::vec3 &value) const;

		/// <summary>
		/// Assign 'value' to a glm::vec4 u named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void set_uniform(std::int32_t location, const glm::vec4 &value) const;

		/// <summary>
		/// Assign 'value' to a glm::mat4 u named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void set_uniform(std::int32_t location, const glm::mat4 &value) const;

		/// <summary>
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		/// <summary>
		/// Assign 'value' to a std::int32_t array u named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		/// <param name="count">Element count</param>
		void set_uniform(std::int32_t location, std::int32_t const * const value, std::uint64_t count) const;
		
		/// <summary>
		/// Returns the location in the s program of the variable 'name'.
		/// </summary>
		/// <param name="name">The variable's name</param>
		/// <returns>The location of the variable</returns>
		std::int32_t get_location(const std::string &name) const;

		std::int32_t ask_location(const std::string &name) const;

	private:
		friend class shader_manager;

	private:
		/// <summary>
		/// Bind the program as current.
		/// </summary>
		void set_active() const;

		void set_uid(shader_uid id_shader);

		/// <summary>
		/// Set s type 'bit'.
		/// </summary>
		/// <param name="bit">OpenGL s bit enum</param>
		void set_bit(std::uint64_t bit);

		/// <summary>
		/// uniform_register OpenGL object.
		/// </summary>
		void create();

		/// <summary>
		/// Unregister OpenGL object and clean resources.
		/// </summary>
		void destroy();

		/// <summary>
		/// Compile the partial s programs.
		/// </summary>
		/// <returns>
		/// True - compiled successfully
		/// False - compilation failure
		/// </returns>
		bool compile_sub_shaders();

		std::uint32_t m_id_object;
		shader_uid m_id_shader;
		std::uint64_t m_shader_bits; // bitmap to check whether the s has already been attached
		std::vector<sub_shader> m_sub_shaders;
	};
}