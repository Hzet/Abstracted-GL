#pragma once

#include "vertex-buffer.hpp"
#include "vertex-layout.hpp"
#include "index-buffer.hpp"

namespace agl
{
	class CVertexArray final
		: public system::IGLObject
	{
	public:
		using system::IGLObject::IGLObject;

		CVertexArray();
		CVertexArray(CVertexArray&&) = default;
		~CVertexArray();

		CVertexArray& operator=(CVertexArray&&) = default;

		virtual void bind() const override;
		virtual void unbind() const override;
		 
		virtual void create() override;
		virtual void destroy() override;

		void setBuffer(const CVertexBuffer &buffer, const CVertexLayout &layout);
		void setBuffer(const CVertexBuffer &vBuffer, const CVertexLayout &layout, const CIndexBuffer &iBuffer);

		std::uint64_t getIndexCount() const;
		std::uint64_t getVertexCount() const;

	private:
		std::uint64_t iCount_;
		std::uint64_t vCount_;
	};
}