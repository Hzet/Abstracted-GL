#pragma once 

#include "window-base.hpp"
#include "shader-program.hpp"
#include "vertex-array.hpp"

namespace agl
{
	class CRenderer
	{
	public:
		void draw(const CVertexArray &vArray, std::uint64_t drawType) const;

		void addShader(std::uint32_t name, CShader &&shader);
		const CShader& getShader(std::uint32_t name) const;

		const CShader& getActiveShader() const;
		void setActiveShader(std::uint32_t name);

	private:
		std::uint32_t active_;
		std::unordered_map<std::uint32_t, CShader> shaders_;
	};
}