template <typename TComponent>
uniform<transform_uniform, TComponent>::uniform()
	: uniform_register<transform_uniform, transformable>{ "model" }
{
}

template <typename TComponent>
void uniform<transform_uniform, TComponent>::send(const shader &sh, const entity &e)
{
	if (m_update_uniform_locations)
	{
		m_transform = sh.get_location(get_indexed_name() + "." + "transform");

		m_update_uniform_locations = false;
	}

	auto const& transform = e.get_component<TComponent>();

	sh.set_uniform(m_transform, transform.get_transform());
}