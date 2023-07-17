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
bool system_register<TGroupName, TDerived>::s_registered = system_register<TGroupName, TDerived>::register_type();
