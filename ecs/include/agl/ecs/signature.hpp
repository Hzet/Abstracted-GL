#pragma once
#include <bitset>

#include "agl/ecs/config.hpp"
#include "agl/ecs/component-type-uid.hpp"
#include "agl/uid/type-unique-identifier.hpp"

namespace agl
{
	/// <summary>
	/// A class to uniquely identify a set of different types.
	/// The sig consists of a bitset where the indices represents the agl::unique_type_id
	/// and the value represents presence of the type.
	/// </summary>
	class signature final
	{
	public:
		template <typename TComponent>
		static std::uint64_t get_index();

		static std::uint64_t get_index(component_type_uid id_component_type);

		/// <summary>
		/// Static creator of signatures.
		/// </summary>
		/// <returns>The sig</returns>
		template <typename... Args> 
		static signature create();
 
		signature();

		/// <summary>
		/// Checks whether the sig includes queried types.
		/// </summary>
		/// <returns>
		/// True - all types are included in the signature.
		/// False - some or all of the types are absent in the signature.
		/// </returns>
		template <typename... Args> 
		bool has_type() const;

		/// <summary>
		/// Attaches the types to the signature.
		/// </summary>
		template <typename... Args> void attach_type();

		/// <summary>
		/// Detaches the types from the signature.
		/// </summary>
		template <typename... Args> void detach_type();

		/// <summary>
		/// Iterate over the sig's types.
		/// </summary>
		/// <param name="index">The index</param>
		/// <returns>
		/// True - sig has 
		/// </returns>
		bool operator[](component_type_uid id_component_type) const;

		/// <summary>
		/// Iterate over the sig's types.
		/// </summary>
		/// <param name="index">The index</param>
		/// <returns>
		/// True - sig has 
		/// </returns>
		bool operator[](std::uint64_t index) const;		

		/// <summary>
		/// Returns the peak, which is the highest used index.
		/// </summary>
		/// <returns>The count</returns>
		std::uint64_t get_count() const;

		/// <summary>
		/// Returns the underlying std::bitset.
		/// </summary>
		/// <returns>The bitset</returns>
		const std::bitset<AGL_MAX_COMPONENTS>& bitset() const;

	private:
		friend struct std::hash<agl::signature>;
		friend bool operator==(const signature &l, const signature &r);
		friend bool operator!=(const signature &l, const signature &r);

		/// <summary>
		/// Implementation of has_type method.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		template <typename TTuple, std::uint64_t... Sequence> bool has_type_impl(std::index_sequence<Sequence...>) const;
		
		/// <summary>
		/// Implementation of attach_type method.
		/// </summary>
		/// <param name=""></param>
		template <typename TTuple, std::uint64_t... Sequence> void attach_type_impl(std::index_sequence<Sequence...>);

		/// <summary>
		/// Implementation of attach_type method.
		/// </summary>
		/// <param name=""></param>
		template <typename T> void attach_type_impl();

		/// <summary>
		/// Implementation of detach_type method.
		/// </summary>
		/// <param name=""></param>
		template <typename TTuple, std::uint64_t... Sequence> void detach_type_impl(std::index_sequence<Sequence...>);

		/// <summary>
		/// Implementation of detach_type method.
		/// </summary>
		/// <param name=""></param>
		template <typename T> void detach_type_impl();
								  
		std::int64_t m_peak;
		std::bitset<AGL_MAX_COMPONENTS> m_signature;
	};

	bool operator==(const signature &l, const signature &r);
	bool operator!=(const signature &l, const signature &r);

#include "agl/ecs/signature.inl"
}

namespace std
{
	template <>
	struct hash<agl::signature>
	{
		size_t operator()(const agl::signature& sig) const noexcept
		{
			return hash<std::bitset<AGL_MAX_COMPONENTS>>{ }(sig.m_signature);
		}
	};
}