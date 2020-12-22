#pragma once

#include <cstdint>
#include <string>

#include "../System/gl-object.hpp"

namespace agl
{
	namespace graphics
	{
		class CTextureBase
			: system::IGLObject
		{
		public:
			using system::IGLObject::IGLObject;

			CTextureBase(const std::uint64_t target);
			CTextureBase(CTextureBase&&) = default;
			virtual ~CTextureBase();

			CTextureBase& operator=(CTextureBase&&) = default;

			void setParameter(const std::uint64_t setting, const std::uint64_t value) const;

			std::uint64_t getTarget() const;

			virtual void create() override;
			virtual void destroy() override;
			virtual void bind() const override;
			virtual void unbind() const override;

			virtual bool loadFromFile(const std::string &filename) = 0;

		private:
			const std::uint64_t target_;
			std::uint32_t textureSlot_;
		};
	}
}