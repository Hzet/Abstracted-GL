template <typename TComponent>
uniform<transform_uniform, TComponent>::uniform()
{
	set_name("model");
}

template <typename TComponent>
void uniform<transform_uniform, TComponent>::send(const shader &s, const entity &e)
{
	auto &transform = e.get_component<TComponent>();
	s.set_uniform(get_name() + "transform", transform.get_transform());
}