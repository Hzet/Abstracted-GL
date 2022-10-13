#include "utility/ecs/registry.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	entity registry::create()
	{
		return create_entity(this);
	}

	void registry::destroy(entity &e)
	{
		if (entity_uid::GetRefCount(e.get_entity_uid()) > 1ul)
			return;

		const auto &sig = e.get_signature();
		for (auto i = 0ul; i < e.get_signature().get_count(); i++)
			if (sig[i])
				this->detach_component(e.get_entity_uid());

		destroy_entity(e);
	}

	std::vector<entity_uid> registry::entities_matching(const signature &sig)
	{
		auto result = std::vector<entity_uid>{};

		for (const auto &e : m_entities)
			if (e.get_signature() == sig)
				result.push_back(e.get_entity_uid());

		return result;
	}

	std::vector<entity_uid> registry::entities_including(const signature &sig)
	{
		auto result = std::vector<entity_uid>{};

		auto include = bool{};
		auto count = max_inclusive_results(sig);

		result.reserve(count);

		for (const auto &e : m_entities)
		{
			if (count == 0)
				break;
			
			include = true;

			if(e.get_signature().get_count() < sig.get_count())
				continue;

			for (auto i = 0ul; i < sig.get_count(); i++)
				if(sig[i])
					if (!e.get_signature()[i])
					{
						include = false;
						break;
					}

			if (include)
			{
				count--;

				result.push_back(e.get_entity_uid());
			}
		}

		result.shrink_to_fit();

		return result;
	}

	std::uint64_t registry::max_inclusive_results(const signature &sig) const
	{
		auto result = std::numeric_limits<std::uint64_t>::max();
		auto count = 0;

		for (auto i = 0ul; i < sig.get_count(); i++)
		{
			if (sig[i])
			{
				count = get_array_count(i);

				if (result > count)
					result = count;
			}
		}

		return result;
	}

	void registry::update()
	{
		registry_system::update(*this);
	}

	registry::registry()
		: registry_system(*this)
		, registry_entity()
		, registry_component_base()
	{
	}

}

