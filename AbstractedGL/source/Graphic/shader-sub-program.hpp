#pragma once 

#include <string>
#include <cstdint>

namespace agl
{
	class CShader;

	namespace utility
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

			bool loadFromFile(const std::string &filename);
			bool loadFromMemory(const char *source, std::uint64_t size);
			bool setSource(const std::string &source);

			bool compile(); // may throw
			void destroy();

			std::uint32_t programID_;
			std::uint64_t type_;
			std::string source_;
		};
	}
}