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
			SElement();
			constexpr SElement(const std::uint64_t t, const std::uint64_t s, const std::uint32_t c, const bool n);

			std::uint64_t type;
			std::uint64_t size;
			std::uint32_t count;
			bool normalized;
		};

		std::uint64_t getStride() const;
		std::uint64_t getCount() const;

		const SElement& operator[](const std::uint64_t index) const;

		template <class T> void addElement();

	private:
		template <class T> static constexpr SElement GetElement();
		template <> static constexpr SElement GetElement<std::uint8_t>();
		template <> static constexpr SElement GetElement<std::uint32_t>();
		template <> static constexpr SElement GetElement<float>();
		template <> static constexpr SElement GetElement<glm::vec2>();
		template <> static constexpr SElement GetElement<glm::vec3>();
		template <> static constexpr SElement GetElement<glm::vec4>();


		static constexpr std::uint64_t GetTypeSize(const std::uint64_t type);

		std::uint64_t stride_;
		std::vector<SElement> elements_;
	};

#include "vertex-layout.inl"
}