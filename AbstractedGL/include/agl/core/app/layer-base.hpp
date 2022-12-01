#pragma once
#include "agl/core/app/layer-type-uid.hpp"

namespace agl
{
	class layer_base
	{
	public:
		virtual ~layer_base() = default;

		layer_type_uid get_layer_uid() const;

		virtual void on_attach() {};
		virtual void on_update() = 0;
		virtual void on_detach() {};

	private:
		friend class layer_manager;

	private:
		layer_type_uid m_id_layer;
	};
}