#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../System/gl-core.hpp"


namespace agl
{
	/// <summary>
	/// Vertex array layout class is responsible for creating the ordered layout out of supported types.
	/// </summary>
	class CVertexLayout
	{
	public:
		/// <summary>
		/// Aggregation structure.
		/// </summary>
		struct SElement
		{
			SElement();
			constexpr SElement(const std::uint64_t t, const std::uint64_t s, const std::uint32_t c, const bool n);

			std::uint64_t type;
			std::uint64_t size;
			std::uint32_t count;
			bool normalized;
		};

		/// <summary>
		/// Get the size of the stride in bytes.
		/// </summary>
		/// <returns>
		/// The size
		/// </return>
		std::uint64_t getStride() const;

		/// <summary>
		/// Get the count of elements
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::uint64_t getCount() const;

		/// <summary>
		/// Get the element.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		const SElement& operator[](const std::uint64_t index) const;

		/// <summary>
		/// Add element of type 'T' to the layout.
		/// </summary>
		template <class T> void addElement();

	private:
		/// <summary>
		/// Helper methods hidden from the user.
		/// </summary>
		/// <returns></returns>
		template <class T> static constexpr SElement GetElement();
		template <> static constexpr SElement GetElement<std::uint8_t>();
		template <> static constexpr SElement GetElement<std::uint32_t>();
		template <> static constexpr SElement GetElement<float>();
		template <> static constexpr SElement GetElement<glm::vec2>();
		template <> static constexpr SElement GetElement<glm::vec3>();
		template <> static constexpr SElement GetElement<glm::vec4>();

		/// <summary>
		/// Get the size of the OpenGL 'type' in bytes.
		/// </summary>
		/// <param name="type">The type</param>
		/// <returns>
		/// The size
		/// </returns>
		static constexpr std::uint64_t GetTypeSize(const std::uint64_t type);

		std::uint64_t stride_;
		std::vector<SElement> elements_;
	};

#include "vertex-layout.inl"
}