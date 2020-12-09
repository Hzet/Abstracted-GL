#pragma once
#include "shader-sub-program.hpp"

#include <vector>

namespace agl
{
	class CShader
	{
	public:
		CShader();
		CShader(CShader &&other);
		~CShader();

		bool attachFromString(std::uint64_t type, const std::string &source);
		bool attachFromFile(std::uint64_t type, const std::string &filename);
		bool attachFromMemory(std::uint64_t type, const char *data, std::uint64_t size);


		bool link();
		void setActive();

		bool hasShader(std::uint64_t bit);
		


	private:
		static constexpr std::uint64_t GetBit(std::uint64_t type);

		void setBit(std::uint64_t bit);

		void destroy();
		bool compileSubshaders();

		bool move_;
		std::uint32_t programID_;
		std::uint64_t shaderBits_; // bitmap to check whether the shader has already been attached
		std::vector<utility::CSubShader> subshaders_;
	};
}