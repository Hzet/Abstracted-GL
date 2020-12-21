#pragma once 

#include <string>
#include <cstdint>

#include "../System/gl-object.hpp"

namespace agl
{
	class CShader;

	namespace graphics
	{
		class CSubShader final
			: protected system::IGLObject
		{
		public:
			using system::IGLObject::IGLObject;

			CSubShader();
			CSubShader(CSubShader&&) = default;
			~CSubShader();

			CSubShader& operator=(CSubShader&&) = default;

		private:
			friend class CShader;
			
			static bool VerifyType(const std::uint64_t type);

			std::uint32_t getID() const;
			std::uint64_t getType() const;

			bool setSource(const std::uint64_t type, const std::string &source);
			bool loadFromFile(const std::uint64_t type, const std::string &filename);
			bool loadFromMemory(const std::uint64_t type, const char *source, std::uint64_t size);

			bool compile(); // may throw

			virtual void create() override;
			virtual void destroy() override;

			std::uint64_t type_;
			std::string source_;
		};
	}
}