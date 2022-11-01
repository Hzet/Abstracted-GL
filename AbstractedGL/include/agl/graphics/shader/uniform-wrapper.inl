template <typename TName, typename TComponent>
uniform_wrapper<TName, TComponent>::uniform_wrapper()
{
	m_uniform = std::make_unique<uniform<TName, TComponent>>();

	m_uniform->m_id_uniform_data_type = TUniformDataTypeUID<TName>::value();
	m_uniform->m_id_component_type_uid = TComponentTypeUID<TComponent>::value();
}

template <typename TName, typename TComponent>
std::unique_ptr<uniform_base> uniform_wrapper<TName, TComponent>::clone(uniform_base const * const dataSource /*= nullptr*/) const
{
	auto result = std::make_unique<uniform<TName, TComponent>>(static_cast<uniform<TName, TComponent> const&>(*m_uniform));

	if (dataSource != nullptr)
		*result = static_cast<uniform<TName, TComponent>const&>(*dataSource);

	return result;
}