template <typename T>
void layer_manager::add_layer()
{
	if (has_layer<T>())
		return;

	auto pair = m_layers.insert(layer_type_uid::get_id<T>(), std::make_unique<T>());
	pair->second->on_attach();
}

template <typename T>
bool layer_manager::has_layer() const
{
	return m_layers.find(layer_type_uid::get_id<T>()) != m_layers.cend();
}

template <typename T>
void layer_manager::remove_layer()
{
	auto found = m_layers.find(layer_type_uid::get_id<T>());
	found->second->on_detach();

	m_layers.erase(found);
}

template <typename T>
layer_base& layer_manager::get_layer()
{
	return m_layers.find(layer_type_uid::get_id<T>())->second;
}

template <typename T>
layer_base const& layer_manager::get_layer() const
{
	return m_layers.find(layer_type_uid::get_id<T>())->second;
}