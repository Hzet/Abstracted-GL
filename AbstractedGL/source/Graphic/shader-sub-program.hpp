#pragma once 

#include <string>
#include <cstdint>

namespace agl
{
	class CShader;

	namespace graphics
	{
		class CSubShader
		{
			friend class CShader;
			
			static bool VerifyType(const std::uint64_t type);

			CSubShader();
			CSubShader(CSubShader&&) = delete;
			CSubShader(const CSubShader&) = delete;
			~CSubShader();

			std::uint32_t getID() const;
			std::uint64_t getType() const;

			bool setSource(const std::uint64_t type, const std::string &source);
			bool loadFromFile(const std::uint64_t type, const std::string &filename);
			bool loadFromMemory(const std::uint64_t type, const char *source, std::uint64_t size);

			bool compile(); // may throw
			void destroy();

			bool move_;
			std::uint32_t programID_;
			std::uint64_t type_;
			std::string source_;
		};
	}
}