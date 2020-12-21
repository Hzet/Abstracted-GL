#pragma once

#include <cstdint>
#include "move-only.hpp"

namespace agl
{
	namespace system
	{
		class IGLObject
			: public CMoveOnly
		{
		public:
			using CMoveOnly::CMoveOnly;

			IGLObject();
			IGLObject(IGLObject&&) = default;
			virtual ~IGLObject() = default;

			IGLObject& operator=(IGLObject&&) = default;

			bool isCreated() const;

			virtual void create() = 0;
			virtual void destroy() = 0;

			virtual void bind() const {};
			virtual void unbind() const {};

		protected:
			std::uint32_t objectID_;
		};
	}
}