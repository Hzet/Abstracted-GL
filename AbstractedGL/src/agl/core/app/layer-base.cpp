#include "agl/core/app/layer-base.hpp"

namespace agl
{
	layer_base::layer_base(layer_type_uid id_layer)
		: m_id_layer{ id_layer }
	{
	}

	layer_type_uid layer_base::get_layer_uid() const
	{
		return m_id_layer;
	}
}