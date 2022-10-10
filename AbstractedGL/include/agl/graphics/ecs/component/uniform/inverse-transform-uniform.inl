template <typename TComponent>
uniform<inverse_transform_uniform, TComponent>::uniform()
{
	set_name("model");
}

template <typename TComponent>
void uniform<inverse_transform_uniform, TComponent>::send(const shader &s, const entity &e)
{
	auto &transform = e.get_component<TComponent>();

	s.set_uniform(get_name() + "inverse_transform", transform.get_inverse_transform());
}