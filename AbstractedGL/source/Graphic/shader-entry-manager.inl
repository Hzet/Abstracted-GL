template <class T>
void CShaderEntryManager::pass(const std::string &name, T value) const
{
	const CShader &shader = CShaderManager::GetShader(entries_.at(name));
	shader.setActive();
	shader.setUniform(name, value);
}