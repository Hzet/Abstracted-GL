#pragma once
#include <memory>
#include <string>

#include "graphics/shader/shader-uid.hpp"
#include "graphics/shader/uniform-data-type-uid.hpp"
#include "utility/ecs/component-type-uid.hpp"

namespace agl
{
	class shader;
	class entity;

	class uniform_base
	{
	public:
		uniform_base() = default;
		uniform_base(const std::string &name);
		virtual ~uniform_base() = default;

		uniform_data_type_uid get_data_type_uid() const;
		component_type_uid get_component_type_uid() const;

		void set_name(const std::string &name);
		const std::string& get_name() const;

		void add_shader_uid(shader_uid id_shader);
		const std::vector<shader_uid>& get_shader_uids() const;
		bool has_shader_uid(shader_uid id_shader) const;
		void remove_shader_uid(shader_uid id_shader);

		virtual void send(const shader &s, const entity &e) = 0;

	protected:
		uniform_base(uniform_data_type_uid id_uniform_data_type, component_type_uid id_component_type);

	private:
		template <typename TData, typename TComponent>
		friend class uniform_wrapper;

		std::string m_name;
		uniform_data_type_uid m_id_uniform_data_type;
		component_type_uid m_id_component_type_uid;
		std::vector<shader_uid> m_id_shader;
	};
}