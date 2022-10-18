template <typename TData>
void uniform_array::add_uniform(shader_uid id_shader)
{
	if (!has_uniform<TData>())
	{
		const auto &group = group_uniform::get_group<TData>();
		auto u = group.get_uniform(group[0ul].get_component_type_uid());

		m_uniforms.push_back(std::move(u));
	}

	auto &u = *get_uniform_pointer<TData>();

	u.set_shader_uid(id_shader);
}

template <typename TData> 
void uniform_array::remove_uniform()
{
	for (auto it = m_uniforms.begin(); it != m_uniforms.end(); ++it)
		if ((*it)->get_data_type_uid() == TUniformDataTypeUID<TData>::value())
		{
			auto &u = *(*it)->get();

			it = m_uniforms.erase(it);

			break;
		}
}

template <typename TData>
TData& uniform_array::get_uniform()
{
	for (auto &v : m_uniforms)
		if (v->get_data_type_uid() == TUniformDataTypeUID<TData>::value())
			return *dynamic_cast<data_uniform<TData>*>(v.get());

	AGL_CORE_ASSERT(false, "Failed to find u");
}

template <typename TData>
const TData& uniform_array::get_uniform() const
{
	for (auto &v : m_uniforms)
		if (v->get_data_type_uid() == TUniformDataTypeUID<TData>::value())
			return *dynamic_cast<data_uniform<TData>*>(v.get());

	AGL_CORE_ASSERT(false, "Failed to find u");
}

template <typename TData>
bool uniform_array::has_uniform()
{
	for (auto &v : m_uniforms)
		if (v->get_data_type_uid() == TUniformDataTypeUID<TData>::value())
			return true;

	return false;
}

template <typename TData> 
uniform_base* uniform_array::get_uniform_pointer()
{
	for (auto &v : m_uniforms)
		if (v->get_data_type_uid() == TUniformDataTypeUID<TData>::value())
			return v.get();

	return nullptr;
}