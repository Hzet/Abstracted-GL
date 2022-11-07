template <typename TGroupName, typename TDerived>
system_register<TGroupName, TDerived>::system_register()
	: system_base(system_type_uid::get_id<TDerived>())
{
}

template <typename TGroupName, typename TDerived>
bool system_register<TGroupName, TDerived>::register_type()
{
	return registry_system::register_system<TGroupName, TDerived>();
}

template <typename TGroupName, typename TDerived>
void system_register<TGroupName, TDerived>::register_me() const
{
	system_register::s_registered;
}

template <typename TGroupName, typename TDerived>
std::unique_ptr<system_base> system_register<TGroupName, TDerived>::clone() const
{
	return std::make_unique<TDerived>(static_cast<TDerived const&>(*this));
}

template <typename TGroupName, typename TDerived>
bool system_register<TGroupName, TDerived>::s_registered = system_register<TGroupName, TDerived>::register_type();
