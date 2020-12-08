template <typename... Args>
void CLogInstance::log(std::string &&message, Args&&... args)
{
	std::string result = combineMessage(std::move(message), parseArgs(std::forward<Args>(args)...));

	streamLock_.lock();

	target_ << result;

	streamLock_.unlock();
}

template <typename... Args>
std::vector<std::string> CLogInstance::parseArgs(Args&&... args) const
{
	std::stringstream ss;

	((ss << args << " "), ...);

	std::string tmp;
	std::vector<std::string> result;
	while (ss >> tmp)
		result.push_back(tmp);

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