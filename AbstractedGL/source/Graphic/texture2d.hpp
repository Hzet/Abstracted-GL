#pragma once

#include <glm/glm.hpp>
#include "texture-base.hpp"

namespace agl
{
	class CTexture2D
		: public graphics::CTextureBase
	{
	public:
		using graphics::CTextureBase::CTextureBase;

		CTexture2D();

		const glm::uvec2& getDimensions() const;

		virtual bool loadFromFile(const std::string &filename) override;

	private:
		glm::uvec2 dimensions_;
	};
}