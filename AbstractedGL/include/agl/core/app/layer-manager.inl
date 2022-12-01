template <typename T>
void layer_manager::add_layer()
{
	if (has_layer<T>())
		return;

	auto layer = std::make_unique<T>();
	layer->m_id_layer = layer_type_uid::get_id<T>();

	m_layers.push_back(std::move(layer));
	m_layers.back()->on_attach();
}

template <typename T>
bool layer_manager::has_layer() const
{
	auto const id_layer = layer_type_uid::get_id<T>();

	for (auto const& layer : m_layers)
		if (layer->get_layer_uid() == id_layer)
			return true;

	return false;
}

template <typename T>
void layer_manager::remove_layer()
{
	auto const id_layer = layer_type_uid::get_id<T>();

	auto found = m_layers.cbegin();

	for (; found != m_layers.cend(); ++found)
		if ((*found)->get_layer_uid() == id_layer)
			break;

	(*found)->on_detach();

	m_layers.erase(found);
}

template <typename T>
layer_base& layer_manager::get_layer()
{
	auto const id_layer = layer_type_uid::get_id<T>();

	for (auto& layer : m_layers)
		if (layer->get_layer_uid() == id_layer)
			return *layer;

	AGL_CORE_ASSERT(false, "Index out of bounds! Layer not present");
	return nullptr;
}

template <typename T>
layer_base const& layer_manager::get_layer() const
{
	auto const id_layer = layer_type_uid::get_id<T>();

	for (auto& layer : m_layers)
		if (layer->get_layer_uid() == id_layer)
			return *layer;

	AGL_ASSERT(false, "Index out of bounds! Layer not present");
	return nullptr;
}