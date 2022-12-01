#include "agl/core/app/layer-base.hpp"

namespace agl
{
	layer_type_uid layer_base::get_layer_uid() const
	{
		return m_id_layer;
	}
}