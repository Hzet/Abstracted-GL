#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "shader-sub-program.hpp"
#include "../System/gl-object.hpp"

namespace agl
{
	class IShaderData;

	class CShader
		: public system::IGLObject
	{
	public:
		using system::IGLObject::IGLObject;

		CShader();
		CShader(CShader&&) = default;
		~CShader();

		CShader& operator=(CShader&&) = default;

		bool attachFromString(std::uint64_t type, const std::string &source);
		bool attachFromFile(std::uint64_t type, const std::string &filename);
		bool attachFromMemory(std::uint64_t type, const char *data, std::uint64_t size);

		bool link();
		void setActive() const;

		bool hasShader(std::uint64_t bit) const;

		void setFloat(const std::string &name, const float value) const;
		void setVec2(const std::string &name, const glm::vec2 &value) const;
		void setVec3(const std::string &name, const glm::vec3 &value) const;
		void setVec4(const std::string &name, const glm::vec4 &value) const;
		void setMat4(const std::string &name, const glm::mat4 &value) const;
		void setInt(const std::string &name, const std::int32_t value) const;
		void setShaderData(const std::string &name, const IShaderData &data) const;
		void setUnsigned(const std::string &name, const std::uint32_t value) const;
		void setIntArray(const std::string &name, std::int32_t const * const value, std::uint64_t count) const;

	private:
		static constexpr std::uint64_t GetBit(std::uint64_t type);

		void setBit(std::uint64_t bit);

		virtual void create() override;
		virtual void destroy() override;

		virtual void bind() const override;

		bool compileSubshaders();

		std::uint64_t shaderBits_; // bitmap to check whether the shader has already been attached

		// TODO - it is used only in compilation, thus is temporary, so it can be removed from here in the future
		std::vector<graphics::CSubShader> subshaders_;
	};
}