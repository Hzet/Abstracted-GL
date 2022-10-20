template <typename TName>
void uniform_array::add_uniform(shader_uid id_shader)
{
	if (!has_uniform<TName>())
		m_uniforms.push_back(uniform_prototyper::get_prototype(TUniformDataTypeUID<TName>::value()));

	for (auto &v : m_uniforms)
		if (v->get_type_uid() == TUniformDataTypeUID<TName>::value())
			v->set_shader_uid(id_shader);
}

template <typename TName>
void uniform_array::remove_uniform()
{
	auto const id_uniform = TUniformDataTypeUID<TName>::value();

	for (auto it = m_uniforms.begin(); it != m_uniforms.end(); ++it)
		if ((*it)->get_type_uid() == id_uniform)
		{
			auto &u = *(*it)->get();

			it = m_uniforms.erase(it);

			break;
		}
}

template <typename TName>
uniform_base& uniform_array::get_uniform()
{
	auto const id_uniform = TUniformDataTypeUID<TName>::value();

	for (auto &v : m_uniforms)
		if (v->get_type_uid() == id_uniform)
			return *v;

	AGL_CORE_ASSERT(false, "Failed to find u");
}

template <typename TName>
const uniform_base& uniform_array::get_uniform() const
{
	auto const id_uniform = TUniformDataTypeUID<TName>::value();

	for (auto &v : m_uniforms)
		if (v->get_type_uid() == id_uniform)
			return *v;

	AGL_CORE_ASSERT(false, "Failed to find u");
}

template <typename TName>
bool uniform_array::has_uniform()
{
	auto const id_uniform = TUniformDataTypeUID<TName>::value();

	for (auto &v : m_uniforms)
		if (v->get_type_uid() == id_uniform)
			return true;

	return false;
}