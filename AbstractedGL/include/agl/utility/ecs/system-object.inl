template <typename TGroupName, typename TDerived>
system_object<TGroupName, TDerived>::system_object()
	: system_base(system_type_uid::get_id<TDerived>())
{
}

template <typename TGroupName, typename TDerived>
void system_object<TGroupName, TDerived>::register_me() const
{
	system_object::Register_;
}

template <typename TGroupName, typename TDerived>
std::unique_ptr<system_base> system_object<TGroupName, TDerived>::clone() const
{
	return std::make_unique<TDerived>(static_cast<TDerived const&>(*this));
}

template <typename TGroupName, typename TDerived>
bool system_object<TGroupName, TDerived>::Register_ = registry_system::system<TGroupName, TDerived>();
