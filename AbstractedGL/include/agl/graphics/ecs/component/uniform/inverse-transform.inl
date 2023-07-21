template <typename TComponent>
uniform<inverse_transform_uniform, TComponent>::uniform()
	: uniform_register<inverse_transform_uniform, transformable>{ "model" }
{
}

template <typename TComponent>
void uniform<inverse_transform_uniform, TComponent>::send(const shader &sh, const entity &e)
{
	if (m_update_uniform_locations)
	{
		m_inverse_transform = sh.get_location(get_indexed_name() + "." + "inverse_transform");

		m_update_uniform_locations = false;
	}

	auto &transform = e.get_component<TComponent>();

	sh.set_uniform(m_inverse_transform, transform.get_inverse_transform());
}
