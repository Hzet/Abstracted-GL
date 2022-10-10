template <typename... Args>
std::string log_instance::get_message(std::string &&message, Args&&... args)
{
	auto  parsed = parse_args(std::forward_as_tuple(std::forward<Args>(args)...), std::make_index_sequence<sizeof...(Args)>{});

	return combine_message(std::move(message), std::move(parsed));
}

template <typename... Args>
void log_instance::log(std::string &&message, Args&&... args)
{
	auto result = get_message(std::move(message), std::forward<Args>(args)...);

	//m_stream_lock.lock();

	std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	m_target << std::put_time(std::localtime(&tt), "%H:%M:%S") << " " << result << '\n';

	//m_stream_lock.unlock();
}

template <typename T>
std::string log_instance::to_string(T &&arg)
{
	auto ss = std::stringstream{};

	ss << arg;

	return ss.str();
}

template <typename Tuple, std::size_t... Sequence>
std::vector<std::string> log_instance::parse_args(Tuple &&t, std::index_sequence<Sequence...>)
{
	auto result = std::vector<std::string>{};

	(result.push_back(to_string(std::get<Sequence>(t))), ...);

	return result;
}

template <typename... Args>
void log::trace(std::string &&message, Args&&... msgs)
{
	m_trace_log->log(m_prefix + "Trace: " + message, std::forward<Args>(msgs)...);
}

template <typename... Args>
void log::info(std::string &&message, Args&&... msgs)
{
	m_info_log->log(m_prefix + "Info: " + message, std::forward<Args>(msgs)...);
}

template <typename... Args>
void log::warn(std::string &&message, Args&&... msgs)
{
	m_warn_log->log(m_prefix + "Warning: " + message, std::forward<Args>(msgs)...);
}

template <typename... Args>
void log::error(std::string &&message, Args&&... msgs)
{
	m_error_log->log(m_prefix + "Error: " + message, std::forward<Args>(msgs)...);
}

template <typename... Args>
void log::debug(std::string &&message, Args&&... msgs)
{
	m_debug_log->log(m_prefix + "Debug error: " + message , std::forward<Args>(msgs)...);
}