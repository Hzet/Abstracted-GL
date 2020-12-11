#pragma once

#include <cstdint>

#include "../System/move-only.hpp"

namespace agl
{
	namespace graphics
	{
		class CBufferBase
			: protected system::CMoveOnly
		{
		public:
			using system::CMoveOnly::CMoveOnly;

			CBufferBase();
			CBufferBase(CBufferBase&&) = default;
			virtual ~CBufferBase() = default;

			CBufferBase& operator=(CBufferBase&&) = default;

			bool isRegistered() const;

			virtual void bind() const = 0u;
			virtual void unbind() const = 0u;

			virtual void create() = 0u;
			virtual void destroy() = 0u;

		protected:
			std::uint32_t bufferID_;
		};
	}
}