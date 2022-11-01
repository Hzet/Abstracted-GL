#pragma once
#include <cstdint>

namespace agl
{
	template <typename TName>
	class TStaticUID
	{
	public:
		enum invalid_type
		{
			INVALID = 0ul
		};

		static TStaticUID create();

		TStaticUID();
		operator std::uint64_t() const;

	private:
		class manager
		{
		public:
			manager();
			std::uint64_t create();

		private:
			std::uint64_t m_counter;
		};

		friend class manager;

		static manager& get_manager();

		TStaticUID(std::uint64_t uid);

		std::uint64_t m_id;
	};

#include "utility/static-unique-identifier.inl"
}