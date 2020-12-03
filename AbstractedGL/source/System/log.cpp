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

	std::unique_ptr<CLogInstance> CLog::Instance_ = std::unique_ptr<CLogInstance>(new CLogInstance(std::cout));

	void CLog::MessageTarget(std::ostream &target)
	{
		Instance_ = std::unique_ptr<CLogInstance>(new CLogInstance(target));
	}
}