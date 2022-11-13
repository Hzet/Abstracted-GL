#pragma once
#include <vector>

#include "agl/graphics/shader/shader-program.hpp"
#include "agl/graphics/shader/shader-uid.hpp"
#include "agl/core/app/resource.hpp"

namespace agl
{
	/// <summary>
	/// A library that stores shaders for different objects to use.
	/// One can define a static variable atop of the object's .cpp file, attach required shaders, link it and then pass it to this class' constructor.
	/// </summary>
	class shader_manager
		: public resource_base
	{
	public:
		shader_uid load_from_file(const std::string &vertex, const std::string &fragment, const std::string &geometry = "", const std::string &tessControl = "", const std::string &tessEvaluation = "", const std::string &compute = "");

		/// <summary>
		/// Return the s with given 'key'.
		/// </summary>
		/// <param name="id_shader">the unique identifier of the 's'</param>
		/// <returns>the s</returns>
		const shader& get_shader(shader_uid id_shader) const;

		shader_uid const& get_shader_uid(std::uint64_t index) const;

		void set_active_shader(shader_uid id_shader);

		shader const& get_active_shader() const;

		/// <summary>
		/// Adds the 's' with unique identifier 'key'.
		/// The 's' must be a ready to use (successfully linked) s, it will not work otherwise.
		/// </summary>
		/// <param name="id_shader">the unique identifier of the 's'</param>
		/// <param name="s">ready to use s object</param>
		shader_uid add_shader(shader &&s);
		
		void link_all_shaders();

	private:
		static std::uint64_t get_index(const shader_uid &id_shader);

	private:
		virtual void dummy() const override {}

	private:
		shader_uid m_active_shader;
		std::vector<shader> m_shaders;
	};
}