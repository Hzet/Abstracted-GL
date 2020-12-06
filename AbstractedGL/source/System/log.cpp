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



	void CLog::traceTarget(std::ostream &target)
	{
		traceLog_ = std::unique_ptr<CLogInstance>(new CLogInstance(target));
	}

	void CLog::infoTarget(std::ostream &target)
	{
		infoLog_ = std::unique_ptr<CLogInstance>(new CLogInstance(target));

	}

	void CLog::warnTarget(std::ostream &target)
	{
		warnLog_ = std::unique_ptr<CLogInstance>(new CLogInstance(target));
	}

	void CLog::errorTarget(std::ostream &target)
	{
		errorLog_ = std::unique_ptr<CLogInstance>(new CLogInstance(target));
	}

	void CLog::criticalTarget(std::ostream &target)
	{
		criticalLog_ = std::unique_ptr<CLogInstance>(new CLogInstance(target));
	}

	const std::string& CLog::getSuffix() const
	{
		return suffix_;
	}

	void CLog::setSuffix(const std::vector<std::string> &suffix)
	{
		suffix_ = "";
		for(const auto &str : suffix)
			suffix_ += str;
	}

	void CLog::setSuffix(const std::string &suffix)
	{
		suffix_ = suffix;
	}

	const std::string& CLog::getPrefix() const
	{
		return prefix_;
	}

	void CLog::setPrefix(const std::vector<std::string> &prefix)
	{
		prefix_ = "";
		for (const auto &str : prefix)
			prefix_ += str;
	}

	void CLog::setPrefix(const std::string &prefix)
	{
		prefix_ = prefix;
	}

	CLog::CLog(std::ostream &t, std::ostream &i, std::ostream &w, std::ostream &e, std::ostream &c)
		: traceLog_(std::unique_ptr<CLogInstance>(new CLogInstance(t))),
		infoLog_(std::unique_ptr<CLogInstance>(new CLogInstance(i))),
		warnLog_(std::unique_ptr<CLogInstance>(new CLogInstance(w))),
		errorLog_(std::unique_ptr<CLogInstance>(new CLogInstance(e))),
		criticalLog_(std::unique_ptr<CLogInstance>(new CLogInstance(c)))
	{
	}



	std::unique_ptr<CLog> CLogger::CoreLog_;
	std::unique_ptr<CLog> CLogger::ClientLog_;

	CLog& CLogger::getCoreLogger()
	{
		if (CoreLog_ == nullptr)
		{
			CoreLog_ = std::unique_ptr<CLog>(new CLog(std::cout, std::cout, std::cerr, std::cerr, std::cerr));
			CoreLog_->setPrefix("[ CORE BEGIN ] ");
			CoreLog_->setSuffix(" [ CORE END ]");
		}

		return *CoreLog_;
	}

	CLog& CLogger::getClientLogger()
	{
		if (ClientLog_ == nullptr)
		{
			ClientLog_ = std::unique_ptr<CLog>(new CLog(std::cout, std::cout, std::cerr, std::cerr, std::cerr));
			ClientLog_->setPrefix("[ CLIENT BEGIN ] ");
			ClientLog_->setSuffix(" [ CLIENT END ]");
		}

		return *ClientLog_;
	}
}