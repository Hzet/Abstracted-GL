#include "agl/uid/type-unique-identifier.hpp"

namespace agl
{
	const std::unordered_map<std::string, std::unordered_map<std::uint64_t, std::string>>& unique_type_id_debug::get_names()
	{
		return get_names_ref();
	}

	std::uint64_t& unique_type_id_debug::get_max_id()
	{
		static auto max_id = std::uint64_t{};

		return max_id;
	}

	std::unordered_map<std::string, std::unordered_map<std::uint64_t, std::string>>& unique_type_id_debug::get_names_ref()
	{
		static auto names_map = std::unordered_map<std::string, std::unordered_map<std::uint64_t, std::string>>{};

		return names_map;
	}
}