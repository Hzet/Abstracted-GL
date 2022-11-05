#pragma once
#include "agl/core/app/layer-type-uid.hpp"

namespace agl
{
	class layer_base
	{
	public:
		layer_base(layer_type_uid id_layer = {});
		virtual ~layer_base() = default;

		layer_type_uid get_layer_uid() const;

		virtual void on_update() = 0;

	private:
		layer_type_uid m_id_layer;
	};
}