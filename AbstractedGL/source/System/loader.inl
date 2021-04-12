template <typename TDerived, typename TData>
template <typename TImporter> 
auto ILoader<TDerived, TData>::loadFromFile(const std::string &filepath)
{
	//return std::invoke(&TImporter::importFrom, TImporter(), *this, loadDataFromFile(filepath));
	return TImporter().importFrom(static_cast<TDerived&>(*this), loadDataFromFile(filepath));
}

template <typename TDerived, typename TData>
template <typename TImporter, typename TReturn> 
void ILoader<TDerived, TData>::saveToFile(TReturn importable, const std::string &filepath)
{
	TData data;
	//std::invoke(&TImporter::exportTo, TImporter(), *this, importable, data);
	TImporter().exportTo(static_cast<TDerived&>(*this), importable, data);

	saveDataToFile(data, filepath);
}

template <typename TDerived, typename TData>
template <typename TImporter, typename TPartData, typename... Args> 
auto ILoader<TDerived, TData>::loadFromData(TPartData data, Args&&... args)
{
	return TImporter().importFrom(static_cast<TDerived&>(*this), data, std::forward<Args>(args)...);
}

template <typename TDerived, typename TData>
template <typename TImporter, typename TReturn, typename TPartData, typename... Args> 
void ILoader<TDerived, TData>::saveToData(TReturn importable, TPartData data, Args&&... args)
{
	TImporter().exportTo(static_cast<TDerived&>(*this), importable, data, std::forward<Args>(args)...);
}