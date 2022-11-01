#include "utility/type-unique-identifier.hpp"

namespace agl
{
	const std::unordered_map<std::string, std::unordered_map<std::uint64_t, std::string>>& TTypeUID_debug::get_names()
	{
		return get_names_ref();
	}

	std::unordered_map<std::string, std::unordered_map<std::uint64_t, std::string>>& TTypeUID_debug::get_names_ref()
	{
		static auto names_map = std::unordered_map<std::string, std::unordered_map<std::uint64_t, std::string>>{};

		return names_map;
	}
}