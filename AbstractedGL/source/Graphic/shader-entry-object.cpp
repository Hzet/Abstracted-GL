#include "shader-entry-object.hpp"

namespace agl
{

	void CShaderEntryObject::redirectEntry(const std::string &name, const CShaderUID &shaderUID)
	{
		entriesManager_.redirectEntry(name, shaderUID);
	}

}