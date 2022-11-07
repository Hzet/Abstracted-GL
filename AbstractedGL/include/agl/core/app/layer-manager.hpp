#pragma once
#include "agl/core/app/resource.hpp"
#include "agl/core/app/layer-base.hpp"
#include "agl/utility/sorted-vector.hpp"

namespace agl
{
	class layer_manager
		: public resource_base
	{
	public:
		template <typename T>
		void add_layer(); 

		template <typename T>
		bool has_layer() const;

		template <typename T>
		void remove_layer();

		template <typename T>
		layer_base& get_layer();

		template <typename T>
		layer_base const& get_layer() const;

		std::uint64_t get_count() const;

		layer_base& operator[](std::uint64_t index);
		layer_base const& operator[](std::uint64_t index) const;

	private:
		virtual void dummy() const override {};

	private:
		sorted_vector<layer_type_uid, std::unique_ptr<layer_base>> m_layers;
	};

#include "agl/core/app/layer-manager.inl"
}