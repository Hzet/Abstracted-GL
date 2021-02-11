#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../System/gl-object.hpp"
#include "../System/gl-core.hpp"
#include "shader-sub-program.hpp"

namespace agl
{
	class IShaderData;

	/// <summary>
	/// The class representing shader program that consists of at least 2 partial shader programs: GL_VERTEX_SHADER and GL_FRAGMENT_SHADER.
	/// </summary>
	class CShader
		: public system::IGLObject
	{
	public:
		using system::IGLObject::IGLObject;

		static CShader LoadFromFile(const std::string &vertex, const std::string &fragment, const std::string &geometry = "", const std::string &tessControl = "", const std::string &tessEvaluation = "", const std::string &compute = "");
		static CShader LoadFromSource(const std::string &vertex, const std::string &fragment, const std::string &geometry = "", const std::string &tessControl = "", const std::string &tessEvaluation = "", const std::string &compute = "");

		/// <summary>
		/// Set shader bits to zero.
		/// </summary>
		CShader();

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		CShader(CShader&&) = default;

		/// <summary>
		/// Destroy the shader program.
		/// </summary>
		~CShader();

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CShader& operator=(CShader&&) = default;

		/// <summary>
		/// Set the partial shader program's 'source' from a string.
		/// </summary>
		/// <param name="type">The type</param>
		/// <param name="source">The source</param>
		/// <returns>
		/// True - success
		/// False - failure, no partial shader has been attached
		/// </returns>
		bool attachFromSource(std::uint64_t type, const std::string &source);

		/// <summary>
		/// Loads the partial shader program's source from a file.
		/// </summary>
		/// <param name="type">The type</param>
		/// <param name="filename">The filename</param>
		/// <returns>
		/// True - success
		/// False - failure, no partial shader has been attached</returns>
		bool attachFromFile(std::uint64_t type, const std::string &filename);

		/// <summary>
		/// Loads the 'source' code for a partial shader program from contiguous array of 'size'.
		/// The partial program is of 'type'.
		/// </summary>
		/// <param name="type"></param>
		/// <param name="data"></param>
		/// <param name="size"></param>
		/// <returns></returns>
		bool attachFromMemory(std::uint64_t type, const char *data, std::uint64_t size);

		/// <summary>
		/// Create and link the partial shader programs together into a single shader program object.
		/// Reports about encountered errors.
		/// </summary>
		/// <returns>
		/// True - linking successful
		/// False - linking failed
		/// </returns>
		bool link();

		/// <summary>
		/// Bind the program as current.
		/// </summary>
		void setActive() const;

		/// <summary>
		/// Check whether the 'bit' partial shader program is a part of this shader program.
		/// </summary>
		/// <param name="bit">OpenGL enum for shader bits</param>
		/// <returns>
		/// True - partial program is attached
		/// False - partial program is not attached
		/// </returns>
		bool hasShader(std::uint64_t bit) const;

		/// <summary>
		/// Assign 'value' to a float uniform named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void setUniform(const std::string &name, const float value) const;

		/// <summary>
		/// Assign 'value' to a std::int32_t uniform named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void setUniform(const std::string &name, const std::int32_t value) const;

		/// <summary>
		/// Assign 'value' to a std::uint32_t uniform named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void setUniform(const std::string &name, const std::uint32_t value) const;

		/// <summary>
		/// Assign 'value' to a glm::vec2 uniform named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void setUniform(const std::string &name, const glm::vec2 &value) const;

		/// <summary>
		/// Assign 'value' to a glm::vec3 uniform named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void setUniform(const std::string &name, const glm::vec3 &value) const;

		/// <summary>
		/// Assign 'value' to a glm::vec4 uniform named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void setUniform(const std::string &name, const glm::vec4 &value) const;

		/// <summary>
		/// Assign 'value' to a glm::mat4 uniform named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		void setUniform(const std::string &name, const glm::mat4 &value) const;

		/// <summary>
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		/// <summary>
		/// Assign 'value' to a std::int32_t array uniform named 'name'.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="value">New value</param>
		/// <param name="count">Element count</param>
		void setUniform(const std::string &name, std::int32_t const * const value, std::uint64_t count) const;


	private:
		/// <summary>
		/// Returns the location in the shader program of the variable 'name'.
		/// </summary>
		/// <param name="name">The variable's name</param>
		/// <returns>The location of the variable</returns>
		std::int32_t getLocation(const std::string &name) const;

		/// <summary>
		/// Set shader type 'bit'.
		/// </summary>
		/// <param name="bit">OpenGL shader bit enum</param>
		void setBit(std::uint64_t bit);

		/// <summary>
		/// Register OpenGL object.
		/// </summary>
		virtual void create() override;

		/// <summary>
		/// Unregister OpenGL object and clean resources.
		/// </summary>
		virtual void destroy() override;

		/// <summary>
		/// Bind the object to the current context.
		/// </summary>
		virtual void bind() const override;

		/// <summary>
		/// Compile the partial shader programs.
		/// </summary>
		/// <returns>
		/// True - compiled successfully
		/// False - compilation failure
		/// </returns>
		bool compileSubshaders();

		std::uint64_t shaderBits_; // bitmap to check whether the shader has already been attached

		// TODO - it is used only in compilation, thus is temporary, so it can be removed from here in the future
		std::vector<graphics::CSubShader> subshaders_;
	};
}