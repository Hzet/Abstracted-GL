#pragma once
#include <memory>
#include <string>

#include "graphics/shader/shader-uid.hpp"
#include "graphics/shader/uniform-type-uid.hpp"
#include "utility/ecs/component-type-uid.hpp"

namespace agl
{
	class shader;
	class entity;

	class uniform_base
	{
	public:
		uniform_base(const std::string &name = "");
		virtual ~uniform_base() = default;

		uniform_type_uid get_type_uid() const;
		component_type_uid get_component_type_uid() const;

		void set_name(const std::string &name, std::int64_t index = -1);
		const std::string& get_name() const;

		void set_shader_uid(shader_uid id_shader);
		shader_uid get_shader_uid() const;

		void send(shader const& sh, entity const& e);

	protected:
		uniform_base(uniform_type_uid id_uniform_type, component_type_uid id_component_type);

		std::string get_index() const;

		virtual void send_uniform(shader const& sh, entity const& e) = 0;
		virtual void update_uniform_locations(shader const& sh) = 0;

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