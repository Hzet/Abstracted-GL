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
		template <typename TData> void add_uniform();
		template <typename TData> void add_uniform(shader_uid id_shader);
		template <typename TData> void add_uniform(std::initializer_list<shader_uid> id_shaders);

		template <typename TData> void remove_uniform();
		template <typename TData> void remove_uniform(shader_uid id_shader);
		template <typename TData> void remove_uniform(std::initializer_list<shader_uid> id_shaders);

		template <typename TData> bool has_uniform();
		template <typename TData> TData& get_uniform();
		template <typename TData> const TData& get_uniform() const;

		void send(const entity &e);

	private:
		template <typename TData> uniform_base* get_uniform_pointer();

		void update_uniform(const signature &sig, std::uint64_t index);

		std::vector<std::unique_ptr<uniform_base>> m_uniforms;
	};

#include "graphics/shader/uniform-array.inl"
}