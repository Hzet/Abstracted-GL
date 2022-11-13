#pragma once
#include <memory>
#include <string>

#include "agl/graphics/shader/shader-uid.hpp"
#include "agl/graphics/shader/uniform-type-uid.hpp"
#include "agl/utility/ecs/component-type-uid.hpp"

namespace agl
{
	class shader;
	class entity;

	class uniform_base
	{
	public:
		uniform_base(const std::string &name = "");
		virtual ~uniform_base() = default;

		uniform_type_uid get_uniform_type_uid() const;
		component_type_uid get_component_type_uid() const;

		bool is_indexed() const;

		void set_name(const std::string &name, std::int64_t index = -1);
		const std::string& get_name() const;
		std::string get_full_name();

		void set_shader_uid(shader_uid id_shader);
		shader_uid get_shader_uid() const;

		virtual void send(shader const& sh, entity const& e) = 0;

	protected:
		uniform_base(uniform_type_uid id_uniform_type, component_type_uid id_component_type);

	protected:
		bool m_update_uniform_locations;

	private:
		template <typename TName, typename TComponent>
		friend class uniform_wrapper;

		std::int64_t m_index; 
		component_type_uid m_id_component_type_uid;
		shader_uid m_id_shader;
		uniform_type_uid m_id_uniform_type;
		std::string m_name;
	};
}