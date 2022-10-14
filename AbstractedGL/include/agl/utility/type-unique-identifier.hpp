#pragma once
#include <iostream>
#include <string>

namespace agl
{
	struct SVoid {};

	template <typename TName, typename T = SVoid>
	class TTypeUID
	{
	public:
		constexpr static TTypeUID<TName> value()
		{
			static TTypeUID<TName> Result(++TTypeUID<TName>::incrementor());

			return Result;
		}
	};

	template <typename TName>
	class TTypeUID<TName, SVoid>
	{
	public:
		enum EInvalid
		{
			INVALID = 0ul
		};

		TTypeUID();

		operator std::uint64_t() const;

	private:
		template <typename TName, typename T>
		friend class TTypeUID;

		constexpr static std::uint64_t& incrementor()
		{
			static std::uint64_t Result = 0ul;

			return Result;
		}

		TTypeUID(std::uint64_t uid);

		std::uint64_t m_id;
	};

	template <typename TName>
	TTypeUID<TName>::TTypeUID()
		: m_id(INVALID)
	{
	}

	template <typename TName>
	TTypeUID<TName>::TTypeUID(std::uint64_t uid)
		: m_id(uid)
	{
	}

	template <typename TName>
	TTypeUID<TName>::operator std::uint64_t() const
	{
		return m_id;
	}

}

/*
#pragma once
#include <string>
#include <bitwizeshift/type-name.hpp>

#define AGL_STR(x) #x

namespace agl
{
	struct SVoid {};

	template <typename TName, typename T = SVoid>
	class TTypeUID
	{
	public:
		constexpr static TTypeUID<TName> value()
		{
			static TTypeUID<TName> Result(++TTypeUID<TName>::incrementor(), Classname());

			return Result;
		}

		constexpr static std::string_view Classname()
		{
			return bitwizeshift::type_name<TName>();
		}
	};

	template <typename TName>
	class TTypeUID<TName, SVoid>
	{
	public:
		enum EInvalid
		{
			INVALID = 0ul
		};

		constexpr TTypeUID();
		constexpr TTypeUID(TTypeUID &&other);
		constexpr TTypeUID(const TTypeUID &other);
		constexpr TTypeUID& operator=(TTypeUID &&other);
		constexpr TTypeUID& operator=(const TTypeUID &other);

		constexpr operator std::uint64_t() const;
		constexpr const std::string_view& name() const;

	private:
		template <typename TName, typename T>
		friend class TTypeUID;

		constexpr static std::uint64_t& incrementor()
		{
			static std::uint64_t Result = 0ul;

			return Result;
		}

		constexpr TTypeUID(std::uint64_t uid, const std::string_view &classname);

		const std::string_view classname_;
		const std::uint64_t m_id;
	};

	template <typename TName>
	constexpr TTypeUID<TName>::TTypeUID()
		: classname_("")
		, m_id(INVALID)
	{
	}

	template <typename TName>
	constexpr TTypeUID<TName>::TTypeUID(TTypeUID &&other)
		: classname_(std::move(other.classname_))
		, m_id(other.m_id)
	{
	}

	template <typename TName>
	constexpr TTypeUID<TName>::TTypeUID(const TTypeUID &other)
		: classname_(other.classname_)
		, m_id(other.m_id)
	{
	}

	template <typename TName>
	constexpr TTypeUID<TName>& TTypeUID<TName>::operator=(TTypeUID &&other)
	{
		classname_ = std::move(other.classname_);
		m_id = other.m_id;

		return *this;
	}

	template <typename TName>
	constexpr TTypeUID<TName>& TTypeUID<TName>::operator=(const TTypeUID &other)
	{
		classname_ = other.classname_;
		m_id = other.m_id;

		return *this;
	}


	template <typename TName>
	constexpr TTypeUID<TName>::operator std::uint64_t() const
	{
		return m_id;
	}


	template <typename TName>
	constexpr const std::string_view& TTypeUID<TName>::name() const
	{
		return classname_;
	}

	template <typename TName>
	constexpr TTypeUID<TName>::TTypeUID(std::uint64_t uid, const std::string_view &classname)
		: classname_(classname)
		, m_id(uid)
	{
	}
}*/