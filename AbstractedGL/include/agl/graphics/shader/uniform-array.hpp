#pragma once
#include <cstdarg>
#include <vector>

#include "agl/graphics/shader/uniform-prototyper.hpp"
#include "agl/debug/assert.hpp"

namespace agl
{
	class entity;
	class shader;
	class signature;

	class uniform_array
	{
	public:
		template <typename TName, typename TComponent> void add_uniform(shader_uid id_shader = {});
		template <typename TName, typename TComponent> void add_uniform(std::initializer_list<shader_uid> id_shaders);

		template <typename TName> void remove_uniform();

		template <typename TName> bool has_uniform();
		template <typename TName> uniform_base& get_uniform();
		template <typename TName> const uniform_base& get_uniform() const;

		void send(const entity &e);

		uniform_base& get_uniform(std::uint64_t index);
		uniform_base const& get_uniform(std::uint64_t index) const;

		std::uint64_t get_count() const;

	private:
		template <typename TName> uniform_base* get_uniform_pointer();

		std::vector<std::unique_ptr<uniform_base>> m_uniforms;
	};

#include "agl/graphics/shader/uniform-array.inl"
}