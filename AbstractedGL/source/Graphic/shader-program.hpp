#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "shader-sub-program.hpp"
#include "../System/move-only.hpp"

namespace agl
{
	class CShader
		: public system::CMoveOnly
	{
	public:
		using system::CMoveOnly::CMoveOnly;

		CShader();
		~CShader();

		bool attachFromString(std::uint64_t type, const std::string &source);
		bool attachFromFile(std::uint64_t type, const std::string &filename);
		bool attachFromMemory(std::uint64_t type, const char *data, std::uint64_t size);

		bool link();
		void setActive();

		bool hasShader(std::uint64_t bit);

		float setFloat(const std::string &name, const float value) const;
		glm::vec2 setVec2(const std::string &name, const glm::vec2 &value) const;
		glm::vec3 setVec3(const std::string &name, const glm::vec3 &value) const;
		glm::vec4 setVec4(const std::string &name, const glm::vec4 &value) const;
		glm::mat4 setMat4(const std::string &name, const glm::mat4 &value) const;
		std::int32_t setInt(const std::string &name, const std::int32_t value) const;
		std::uint32_t setUnsigned(const std::string &name, const std::uint32_t value) const;
		std::vector<std::int32_t> setIntArray(const std::string &name, std::int32_t const * const value, std::uint64_t count) const;

	private:
		static constexpr std::uint64_t GetBit(std::uint64_t type);

		void setBit(std::uint64_t bit);

		void destroy();
		bool compileSubshaders();

		std::uint32_t programID_;
		std::uint64_t shaderBits_; // bitmap to check whether the shader has already been attached
		std::vector<graphics::CSubShader> subshaders_;
	};
}