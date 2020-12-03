template <typename... Args>
void CLogInstance::log(Args&&... msgs)
{
	((target_ << msgs << ' '), ...) << '\n';
}

template <typename... Args>
static void CLog::SendMessage(Args&&... msgs)
{
	Instance_->log(std::forward<Args>(msgs)...);
}