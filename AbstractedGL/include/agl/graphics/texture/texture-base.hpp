#pragma once
#include <cstdint>
#include <string>
#include <glm/glm.hpp>

#include "agl/graphics/texture/texture-type.hpp"
#include "agl/graphics/texture/texture-uid.hpp"
#include "agl/system/glcore/destructive-move.hpp"

namespace agl
{
	/// <summary>
	/// The base class for texture providing gl_object implementation
	/// and general texture specific methods.
	/// </summary>
	class texture_base
		: public destructive_move
	{
	public:
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

		bool is_created() const;

		std::string const& get_filepath() const;

		glm::vec3 get_size() const;

		/// <summary>
		/// Pure virtual method to get the texture's target.
		/// </summary>
		/// <returns>
		/// OpenGL texture target enum
		/// </returns>
		texture_type get_type() const;


	protected:
		texture_base(texture_type type);

		/// <summary>
		/// uniform_register OpenGL object.
		/// </summary>
		void create();

		/// <summary>
		/// Unregister the OpenGL object and clear resources.
		/// </summary>
		void destroy();

		/// <summary>
		/// Bind OpenGL object.
		/// </summary>
		void bind() const;

		/// <summary>
		/// Unbind OpenGL object.
		/// </summary>
		void unbind() const;

	protected:
		std::string m_filepath;
		glm::vec3 m_size;
		texture_type m_type;

	private:
		std::uint32_t m_id_object;
		texture_uid m_id_texture;

	private:
		friend class texture_manager;
	};
}