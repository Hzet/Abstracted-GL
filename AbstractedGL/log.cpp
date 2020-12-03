#include "log.hpp"

namespace agl
{

	CLogInstance::CLogInstance(std::ostream &target)
		: target_(target)
	{
	}

	CLogInstance::CLogInstance(const CLogInstance &other)
		: target_(other.target_)
	{
	}

	void CLogInstance::log(std::initializer_list<std::string> msgs)
	{
		for (const auto &str : msgs)
			target_ << str << std::endl;
	}

	std::unique_ptr<CLogInstance> Instance_ = {};

	void CLog::SendMessage(std::initializer_list<std::string> msgs)
	{
		Instance_->log(msgs);
	}

	void CLog::MessageTarget(std::ostream &target)
	{
		Instance_ = std::unique_ptr<CLogInstance>(new CLogInstance(target));
	}
}