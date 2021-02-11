#include "renderer.hpp"

#include "../System/gl-core.hpp"

namespace agl
{
	void CRenderer::draw(const CVertexArray &vArray, std::uint64_t drawType) const
	{
		vArray.bind();
		
		if (vArray.getIndexCount() == 0u)
			AGL_CALL(glDrawArrays(drawType, 0u, vArray.getVertexCount()));
		else
			AGL_CALL(glDrawElements(drawType, vArray.getIndexCount(), GL_UNSIGNED_INT, 0u));
	}
}