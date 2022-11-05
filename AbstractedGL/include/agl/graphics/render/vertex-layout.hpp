#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "agl/system/glcore/gl-core.hpp"

namespace agl
{
	/// <summary>
	/// Vertex array layout class is responsible for creating the ordered layout out of supported types.
	/// </summary>
	class vertex_layout
	{
	public:
		/// <summary>
		/// Aggregation structure.
		/// </summary>
		struct element
		{
			std::uint32_t type;
			std::uint32_t size;
			std::uint32_t count;
			std::uint32_t offset;
			bool normalized;
		};

		vertex_layout();

		/// <summary>
		/// Get the size of the stride in bytes.
		/// </summary>
		/// <returns>
		/// The size
		/// </returns>
		std::uint32_t get_size() const;

		/// <summary>
		/// Get the count of elements
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::uint32_t get_count() const;

		/// <summary>
		/// Get the element.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		const element& operator[](const std::uint32_t index) const;

		/// <summary>
		/// Add element of type 'T' to the layout.
		/// </summary>
		template <class T> void add_element();

	private:
		/// <summary>
		/// Helper methods hidden from the user.
		/// </summary>
		/// <returns></returns>
		template <class T> element get_element();
		template <> element get_element<std::uint8_t>();
		template <> element get_element<std::uint32_t>();
		template <> element get_element<float>();
		template <> element get_element<glm::vec2>();
		template <> element get_element<glm::vec3>();
		template <> element get_element<glm::vec4>();

		/// <summary>
		/// Get the size of the OpenGL 'type' in bytes.
		/// </summary>
		/// <param name="type">The type</param>
		/// <returns>
		/// The size
		/// </returns>
		static constexpr std::uint32_t get_type_size(const std::uint32_t type);

		std::uint32_t m_stride;
		std::vector<element> m_elements;
	};

#include "agl/graphics/render/vertex-layout.inl"
}