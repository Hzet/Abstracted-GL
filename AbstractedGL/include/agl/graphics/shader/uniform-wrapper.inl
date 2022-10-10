template <typename TData, typename TComponent>
uniform_wrapper<TData, TComponent>::uniform_wrapper()
{
	uniform_ = std::make_unique<uniform<TData, TComponent>>();

	uniform_->m_id_uniform_data_type = TUniformDataTypeUID<TData>::value();
	uniform_->m_id_component_type_uid = TComponentTypeUID<TComponent>::value();
}

template <typename TData, typename TComponent>
std::unique_ptr<uniform_base> uniform_wrapper<TData, TComponent>::clone(uniform_base const * const dataSource /*= nullptr*/) const
{
	auto result = std::make_unique<uniform<TData, TComponent>>(static_cast<uniform<TData, TComponent> const&>(*uniform_));

	if (dataSource != nullptr)
	{
		auto &destination = *dynamic_cast<data_uniform<TData>*>(result.get());
		const auto &source = *dynamic_cast<data_uniform<TData> const * const>(dataSource);

		destination = source;
	}

	return result;
}