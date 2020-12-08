#include "log.hpp"

#include <regex>

namespace agl
{
	static std::uint64_t getParam(const std::string &token)
	{
		//AGL_CORE_ASSERT(token.size() < 3u, "Invalid token!");
		return std::stoul(token.substr(1, token.size() - 2u));
	}

	CLogInstance::CLogInstance(std::ostream &target)
		: target_(target)
	{
	}

	CLogInstance::CLogInstance(const CLogInstance &other)
		: target_(other.target_)
	{
	}

	std::vector<std::smatch> parseString(const std::string &str, const std::string &pattern)
	{
		const std::regex rpattern(pattern);
		const std::sregex_iterator begin = std::sregex_iterator(str.cbegin(), str.cend(), rpattern);
		const std::sregex_iterator end = std::sregex_iterator();

		std::vector<std::smatch> result(std::distance(begin, end));
		std::size_t i = 0u;
		for (auto it = begin; it != end; ++it, i++)
			result[i] = *it;

		return result;
	}

	static std::string insertDefaultArguments(const std::string &message, std::vector<std::string> &args)
	{
		std::string result = message;
		const std::vector<std::smatch> parsed = parseString(message, "\\{\\}");

		std::int64_t insertOffset = 0u;
		std::uint64_t currentArgument = 0u;
		for (const auto &v : parsed)
		{
			const std::string &param = args[currentArgument];
			const auto insertAt = result.begin() + (v.position() + insertOffset == result.size() ? result.size() - 1u : v.position() + insertOffset);

			result.insert(insertAt, param.cbegin(), param.cend());
			insertOffset += param.size();

			result.erase(result.begin() + v.position() + insertOffset, result.begin() + v.position() + insertOffset + v.str().size());
			insertOffset -= v.str().size();

			currentArgument++;
		}

		args.erase(args.begin(), args.begin() + currentArgument);

		return result;
	}

	static std::string insertIndexedArguments(const std::string &message, const std::vector<std::string> &args)
	{
		std::string result = message;
		const std::vector<std::smatch> parsed = parseString(message, "\\{[0-9]\\}");

		std::int64_t insertOffset = 0u;
		for (const auto &v : parsed)
		{
			const std::string &param = args[getParam(v.str())];
			const auto insertAt = result.begin() + (v.position() + insertOffset == result.size() ? result.size() - 1u : v.position() + insertOffset);

			result.insert(insertAt, param.cbegin(), param.cend());
			insertOffset += param.size();

			result.erase(result.begin() + v.position() + insertOffset, result.begin() + v.position() + insertOffset + v.str().size());
			insertOffset -= v.str().size();
		}
		return result;
	}

	std::string CLogInstance::combineMessage(std::string &&message, std::vector<std::string> &&args) const
	{
		std::string result;

		result = insertDefaultArguments(message, args);
		result = insertIndexedArguments(result, args);

		return result;
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
		for (const auto &str : suffix)
			suffix_ += str;
		suffix_.insert(suffix_.begin(), '\n');
		suffix_ += "\n";
	}

	void CLog::setSuffix(const std::string &suffix)
	{
		suffix_ = suffix;
		suffix_.insert(suffix_.begin(), '\n');
		suffix_ += "\n";
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
		prefix_.insert(prefix_.end(), '\n');
	}

	void CLog::setPrefix(const std::string &prefix)
	{
		prefix_ = prefix;
		prefix_.insert(prefix_.end(), '\n');
	}

	CLog::CLog(std::ostream &t, std::ostream &i, std::ostream &w, std::ostream &e, std::ostream &c)
		: traceLog_(std::unique_ptr<CLogInstance>(new CLogInstance(t))),
		infoLog_(std::unique_ptr<CLogInstance>(new CLogInstance(i))),
		warnLog_(std::unique_ptr<CLogInstance>(new CLogInstance(w))),
		errorLog_(std::unique_ptr<CLogInstance>(new CLogInstance(e))),
		criticalLog_(std::unique_ptr<CLogInstance>(new CLogInstance(c)))
#ifdef AGL_DEBUG
		, debugLog_(std::unique_ptr<CLogInstance>(new CLogInstance(std::cerr)))
#endif
	{
	}



	std::unique_ptr<CLog> CLogger::CoreLog_;
	std::unique_ptr<CLog> CLogger::ClientLog_;

	CLog& CLogger::getCoreLogger()
	{
		if (CoreLog_ == nullptr)
		{
			CoreLog_ = std::unique_ptr<CLog>(new CLog(std::cout, std::cout, std::cerr, std::cerr, std::cerr));
			CoreLog_->setPrefix("[ CORE BEGIN ]");
			CoreLog_->setSuffix("[ CORE END ]");
		}

		return *CoreLog_;
	}

	CLog& CLogger::getClientLogger()
	{
		if (ClientLog_ == nullptr)
		{
			ClientLog_ = std::unique_ptr<CLog>(new CLog(std::cout, std::cout, std::cerr, std::cerr, std::cerr));
			ClientLog_->setPrefix("[ CLIENT BEGIN ]");
			ClientLog_->setSuffix("[ CLIENT END ]");
		}

		return *ClientLog_;
	}
}