#pragma once
#include <cstddef>

#include "agl/core/app/resource-type-uid.hpp"
#include "agl/core/app/resource-destructor.hpp"

namespace agl
{
	class resource
	{
	public:
		template <typename T, typename... TArgs>
		static resource create(TArgs&&... args);

	public:
		resource() = default;
		resource(resource&&) = default;
		resource(resource const&) = delete;
		resource& operator=(resource&&) = default;
		resource& operator=(resource const&) = delete;
		~resource();

		void reset();

		template <typename T, typename... TArgs>
		void emplace(TArgs&&... args);

		template <typename T>
		T& get();

		bool is_any() const;

		resource_type_uid get_id() const;

	private:
		std::unique_ptr<resource_destructor_base> m_destructor;
		resource_type_uid m_id;
		std::vector<std::byte> m_buffer;
	};

#include "agl/core/app/resource.inl"

}

