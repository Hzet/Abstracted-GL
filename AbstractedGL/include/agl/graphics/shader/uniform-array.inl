template <typename TName, typename TComponent>
void uniform_array::add_uniform(shader_uid id_shader)
{
	if (!has_uniform<TName>())
	{
		auto u = uniform_prototyper::get_prototype(uniform_type_uid::get_id<TName>(), component_type_uid::get_id<TComponent>());

		m_uniforms.push_back(std::move(u));
	}

	auto &u = *get_uniform_pointer<TName>();

	u.add_shader_uid(id_shader);
}

template <typename TName, typename TComponent>
void uniform_array::add_uniform(std::initializer_list<shader_uid> id_shader)
{
	if (!has_uniform<TName>())
	{
		auto u = uniform_prototyper::get_prototype(uniform_type_uid::get_id<TName>(), component_type_uid::get_id<TComponent>());

		m_uniforms.push_back(std::move(u));
	}

	auto &u = *get_uniform_pointer<TName>();

	u.add_shader_uid(id_shader);
}


template <typename TName>
void uniform_array::remove_uniform()
{
	for (auto it = m_uniforms.cbegin(); it != m_uniforms.cend(); ++it)
		if ((*it)->get_uniform_type_uid() == uniform_type_uid::get_id<TName>())
		{
			auto &u = *(*it)->get();

			it = m_uniforms.erase(it);

			break;
		}
}

template <typename TName>
uniform_base& uniform_array::get_uniform()
{
	for (auto &v : m_uniforms)
		if (v->get_uniform_type_uid() == uniform_type_uid::get_id<TName>())
			return *v;

	AGL_CORE_ASSERT(false, "Failed to find u");
}

template <typename TName>
const uniform_base& uniform_array::get_uniform() const
{
	for (auto &v : m_uniforms)
		if (v->get_uniform_type_uid() == uniform_type_uid::get_id<TName>())
			return *v;

	AGL_CORE_ASSERT(false, "Failed to find u");
}

template <typename TName>
bool uniform_array::has_uniform()
{
	for (auto &v : m_uniforms)
		if (v->get_uniform_type_uid() == uniform_type_uid::get_id<TName>())
			return true;

	return false;
}

template <typename TName>
uniform_base* uniform_array::get_uniform_pointer()
{
	for (auto &v : m_uniforms)
		if (v->get_uniform_type_uid() == uniform_type_uid::get_id<TName>())
			return v.get();

	return nullptr;
}