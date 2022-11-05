#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

#include "agl/system/debug/assert.hpp"

namespace agl
{
	template <typename TName>
	class unique_type_id
	{
	public:
		enum invalid_type
		{
			INVALID = 0ul
		};

	public:
		template <typename T>
		static unique_type_id<TName> get_id();

		static std::unordered_map<std::uint64_t, std::string> const& get_names();

		static std::string const& get_name(std::uint64_t id);

	public:
		unique_type_id();

		operator std::uint64_t() const;

	private:
		static std::uint64_t& incrementor();

	private:
		unique_type_id(std::uint64_t uid);

		std::uint64_t m_id;
	};

	class unique_type_id_debug
	{
	public:
		static const std::unordered_map<std::string, std::unordered_map<std::uint64_t, std::string>>& get_names();

	private:
		template <typename TName>
		friend class unique_type_id;

	private:
		static std::unordered_map<std::string, std::unordered_map<std::uint64_t, std::string>>& get_names_ref();
	};

#include "agl/utility/type-unique-identifier.inl"
}