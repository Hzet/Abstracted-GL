template <class T>
void IShaderEntry::passEntry(const std::string &name, T value) const
{
	pass(name_ + "." + name, std::forward<T>(value));
}
