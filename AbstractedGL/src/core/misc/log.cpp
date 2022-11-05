#include "agl/core/misc/log.hpp"

#include <regex>

namespace agl
{
	static std::uint64_t get_param(const std::string &token)
	{
		//AGL_CORE_ASSERT(token.size() < 3u, "Invalid token!");
		return std::stoul(token.substr(1, token.size() - 2u));
	}

	log_instance::log_instance(std::ostream &target)
		: m_target(target)
	{
	}

	log_instance::log_instance(const log_instance &other)
		: m_target(other.m_target)
	{
	}

	std::vector<std::smatch> parse_string(const std::string &str, const std::string &pattern)
	{
		const auto rpattern = std::regex{ pattern };
		const auto begin = std::sregex_iterator(str.cbegin(), str.cend(), rpattern);
		const auto end = std::sregex_iterator();

		auto result = std::vector<std::smatch>(std::distance(begin, end));
		std::size_t i = 0u;
		for (auto it = begin; it != end; ++it, i++)
			result[i] = *it;

		return result;
	}

	static std::string insert_default_arguments(const std::string &message, std::vector<std::string> &args)
	{
		auto result = message;
		const auto parsed = parse_string(message, "\\{\\}");

		auto insertOffset = 0;
		auto currentArgument = 0u;
		for (const auto &v : parsed)
		{
			const auto &param = args[currentArgument];
			const auto offset = (v.position() + insertOffset == result.size() ? result.size() - 1u : v.position() + insertOffset);
			const auto insertAt = result.begin() + offset;

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
		auto result = message;
		const auto parsed = parse_string(message, "\\{[0-9]\\}");

		auto insertOffset = 0u;
		for (const auto &v : parsed)
		{
			const std::string &param = args[get_param(v.str())];
			const auto insertAt = result.begin() + (v.position() + insertOffset == result.size() ? result.size() - 1u : v.position() + insertOffset);

			result.insert(insertAt, param.cbegin(), param.cend());
			insertOffset += param.size();

			result.erase(result.begin() + v.position() + insertOffset, result.begin() + v.position() + insertOffset + v.str().size());
			insertOffset -= v.str().size();
		}
		return result;
	}

	std::string log_instance::combine_message(std::string &&message, std::vector<std::string> &&args)
	{
		auto result = std::string{};

		result = insert_default_arguments(message, args);
		result = insertIndexedArguments(result, args);

		return result;
	}

	void log::set_trace_target(std::ostream &target)
	{
		m_trace_log = std::unique_ptr<log_instance>(new log_instance(target));
	}

	void log::set_info_target(std::ostream &target)
	{
		m_info_log = std::unique_ptr<log_instance>(new log_instance(target));

	}

	void log::set_warn_target(std::ostream &target)
	{
		m_warn_log = std::unique_ptr<log_instance>(new log_instance(target));
	}

	void log::set_error_target(std::ostream &target)
	{
		m_error_log = std::unique_ptr<log_instance>(new log_instance(target));
	}

	const std::string& log::get_prefix() const
	{
		return m_prefix;
	}

	void log::set_prefix(const std::vector<std::string> &prefix)
	{
		m_prefix = "";
		for (const auto &str : prefix)
			m_prefix += str;
	}

	void log::set_prefix(const std::string &prefix)
	{
		m_prefix = prefix;
	}

	log::log(std::ostream &t, std::ostream &i, std::ostream &w, std::ostream &e, std::ostream &d)
		: m_trace_log(std::unique_ptr<log_instance>(new log_instance(t))),
		m_info_log(std::unique_ptr<log_instance>(new log_instance(i))),
		m_warn_log(std::unique_ptr<log_instance>(new log_instance(w))),
		m_error_log(std::unique_ptr<log_instance>(new log_instance(e))),
		m_debug_log(std::unique_ptr<log_instance>(new log_instance(d)))
	{
	}

	std::unique_ptr<log> logger::m_core_log;
	std::unique_ptr<log> logger::m_client_log;

	log& logger::get_core_logger()
	{
		if (m_core_log == nullptr)
		{
			m_core_log = std::unique_ptr<log>(new log(std::cout, std::cout, std::cerr, std::cerr, std::cerr));
			m_core_log->set_prefix("Core: ");
		}

		return *m_core_log;
	}

	log& logger::get_client_logger()
	{
		if (m_client_log == nullptr)
		{
			m_client_log = std::unique_ptr<log>(new log(std::cout, std::cout, std::cerr, std::cerr, std::cerr));
			m_client_log->set_prefix("Client: ");
		}

		return *m_client_log;
	}
}