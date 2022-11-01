#pragma once
#include <cstdarg>
#include <vector>

#include "graphics/shader/uniform-prototyper.hpp"
#include "system/debug/assert.hpp"

namespace agl
{
	class entity;
	class shader;
	class signature;

	class uniform_array
	{
	public:
		template <typename TName, typename TComponent> void add_uniform(shader_uid id_shader = shader_uid::INVALID);

		template <typename TName> void remove_uniform();

		template <typename TName> bool has_uniform();
		template <typename TName> uniform_base& get_uniform();
		template <typename TName> const uniform_base& get_uniform() const;

		void send(const entity &e);

	private:
		template <typename TName> uniform_base* get_uniform_pointer();

		std::vector<std::unique_ptr<uniform_base>> m_uniforms;
	};

#include "graphics/shader/uniform-array.inl"
}