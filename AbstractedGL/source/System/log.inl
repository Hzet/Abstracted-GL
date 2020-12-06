template <typename... Args>
void CLogInstance::log(Args&&... msgs)
{
	//((target_ << msgs << ' '), ...) << '\n';
	(target_ << ... << msgs) << '\n';
}

template <typename... Args> 
void CLog::trace(Args&&... msgs)
{
	traceLog_->log(prefix_, "Trace: ", std::forward<Args>(msgs)..., suffix_);
}

template <typename... Args> 
void CLog::info(Args&&... msgs)
{
	infoLog_->log(prefix_, "Info: ", std::forward<Args>(msgs)..., suffix_);
}

template <typename... Args> 
void CLog::warn(Args&&... msgs)
{
	warnLog_->log(prefix_, "Warning: ", std::forward<Args>(msgs)..., suffix_);
}

template <typename... Args> 
void CLog::error(Args&&... msgs)
{
	errorLog_->log(prefix_, "Error: ", std::forward<Args>(msgs)..., suffix_);
}

template <typename... Args> 
void CLog::critical(Args&&... msgs)
{
	criticalLog_->log(prefix_, "Critical error: ", std::forward<Args>(msgs)..., suffix_);
}

template <typename... Args>
void CLog::debug(Args&&... msgs)
{
	criticalLog_->log(prefix_, "Debug error: ", std::forward<Args>(msgs)..., suffix_);
}