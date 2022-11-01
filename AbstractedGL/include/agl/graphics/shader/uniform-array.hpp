#pragma once
#include <cstdarg>
#include <vector>

#include "graphics/shader/uniform-group.hpp"
#include "system/debug/assert.hpp"

namespace agl
{
	class entity;
	class shader;
	class signature;

	class uniform_array
	{
	public:
		template <typename TData, typename TComponent> void add_uniform(shader_uid id_shader = shader_uid::INVALID);

		template <typename TData> void remove_uniform();

		template <typename TData> bool has_uniform();
		template <typename TData> TData& get_uniform();
		template <typename TData> const TData& get_uniform() const;

		void send(const entity &e);

	private:
		template <typename TData> uniform_base* get_uniform_pointer();

		std::vector<std::unique_ptr<uniform_base>> m_uniforms;
	};

#include "graphics/shader/uniform-array.inl"
}