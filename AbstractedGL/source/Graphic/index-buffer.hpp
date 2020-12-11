#pragma once

#include "buffer-base.hpp"

namespace agl
{
	class CIndexBuffer final
		: public graphics::CBufferBase
	{
	public:
		using graphics::CBufferBase::CBufferBase;

		CIndexBuffer();
		CIndexBuffer(CIndexBuffer&&) = default;
		~CIndexBuffer();

		CIndexBuffer& operator=(CIndexBuffer&&) = default;

		virtual void bind() const override;
		virtual void unbind() const override;
		 
		virtual void create() override;
		virtual void destroy() override;

		void allocate(std::uint32_t const * const data, std::uint64_t count);
		void buffer(std::uint32_t const * const data, std::uint64_t offset, std::uint64_t count);

		std::uint64_t getCount() const;

	private:
		std::uint64_t count_;
	};
}