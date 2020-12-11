#pragma once

#include "buffer-base.hpp"

namespace agl
{
	class CVertexBuffer final
		: public graphics::CBufferBase
	{
	public:
		using graphics::CBufferBase::CBufferBase;

		CVertexBuffer();
		CVertexBuffer(CVertexBuffer&&) = default;
		~CVertexBuffer();

		CVertexBuffer& operator=(CVertexBuffer&&) = default;

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void create() override;
		virtual void destroy() override;

		void allocate(void const * const data, const std::uint64_t size, const std::uint64_t count); // data, overall size, vertex count (amount of strides)
		void buffer(void const * const data, const std::uint64_t offset, const std::uint64_t size);

		std::uint64_t getSize() const;
		std::uint64_t getCount() const;

	private:
		std::uint64_t size_;
		std::uint64_t count_;
	};

}