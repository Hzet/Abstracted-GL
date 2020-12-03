template <typename... Args>
void CLogInstance::log(Args&&... msgs)
{
	//((target_ << msgs << ' '), ...) << '\n';
	(target_ << ... << msgs) << '\n';
}

template <typename... Args>
void CLog::SendMessage(Args&&... msgs)
{
	Instance_->log(std::forward<Args>(msgs)...);
}

template <typename... Args> 
void CLog::SendOneMessage(std::ostream &target, Args&&... msgs)
{
	std::ostream &prevTarget = Instance_->target_;

	MessageTarget(target);
	SendMessage(std::forward<Args>(msgs)...);
	MessageTarget(prevTarget);
}