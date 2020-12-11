#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../System/gl-core.hpp"


namespace agl
{
	class CVertexLayout
	{
	public:
		struct SElement
		{
			std::uint64_t type;
			std::uint64_t size;
			std::uint32_t count;
			bool normalized;
		};

		std::uint64_t getStride() const;
		std::uint64_t getCount() const;

		const SElement& operator[](const std::uint64_t index) const;

		template <typename T> void addElement();
		template <> void addElement<std::uint8_t>();
		template <> void addElement<std::uint32_t>();
		template <> void addElement<float>();
		template <> void addElement<glm::vec2>();
		template <> void addElement<glm::vec3>();
		template <> void addElement<glm::vec4>();

	private:
		static std::uint64_t GetTypeSize(const std::uint64_t type);

		std::uint64_t stride_;
		std::vector<SElement> elements_;
	};

#include "vertex-layout.inl"
}