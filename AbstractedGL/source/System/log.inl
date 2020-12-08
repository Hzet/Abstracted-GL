template <typename... Args>
void CLogInstance::log(std::string &&message, Args&&... args)
{

	std::vector<std::string> parsed = parseArgs(std::forward_as_tuple(std::forward<Args>(args)...), std::make_index_sequence<sizeof...(Args)>{});

	std::string result = combineMessage(std::move(message), std::move(parsed));

	streamLock_.lock();

	target_ << result;

	streamLock_.unlock();
}

template <typename T>
std::string CLogInstance::toString(T &&arg) const
{
	std::stringstream ss;

	ss << arg;

	return ss.str();
}

template <typename Tuple, std::size_t... Sequence>
std::vector<std::string> CLogInstance::parseArgs(Tuple &&t, std::index_sequence<Sequence...>) const
{
	std::vector<std::string> result;

	(result.push_back(toString(std::get<Sequence>(t))), ...);

	return result;
}

template <typename... Args>
void CLog::trace(std::string &&message, Args&&... msgs)
{
	traceLog_->log(prefix_ + "Trace: " + message + suffix_, std::forward<Args>(msgs)...);
}

template <typename... Args>
void CLog::info(std::string &&message, Args&&... msgs)
{
	infoLog_->log(prefix_ + "Info: " + message + suffix_, std::forward<Args>(msgs)...);
}

template <typename... Args>
void CLog::warn(std::string &&message, Args&&... msgs)
{
	warnLog_->log(prefix_ + "Warning: " + message + suffix_, std::forward<Args>(msgs)...);
}

template <typename... Args>
void CLog::error(std::string &&message, Args&&... msgs)
{
	errorLog_->log(prefix_ + "Error: " + message + suffix_, std::forward<Args>(msgs)...);
}

template <typename... Args>
void CLog::critical(std::string &&message, Args&&... msgs)
{
	criticalLog_->log(prefix_ + "Critical error: " + message + suffix_, std::forward<Args>(msgs)...);
}


#ifdef AGL_DEBUG
template <typename... Args>
void CLog::debug(std::string &&message, Args&&... msgs)
{
	debugLog_->log(prefix_ + "Debug error: " + message + suffix_, std::forward<Args>(msgs)...);
}
#endif