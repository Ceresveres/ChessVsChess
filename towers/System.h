#pragma once
#include "Archetype.h"
#include "Component.h"
#include "ECS.h"
#include <vector>
#include <functional>
#include <cstdint>
#include <bit>

class ECS;
class ComponentBase;
struct Archetype;
class SystemBase
{
public:
	virtual ~SystemBase() {}

	virtual ComponentMask GetMask() const = 0;

	virtual void DoAction(const float elapsedTime, Archetype* archetype) = 0;
};


class ECS;
class ComponentBase;
struct Archetype;
template<class... Cs>
class System : public SystemBase
{
public:

	friend class ECS;

	typedef std::function<void(const float, const std::vector<uint32_t>&, Cs*...)> Func;

	System(ECS& ecs, const std::uint8_t& layer);

	virtual ComponentMask GetMask() const override;

	void Action(Func func);

protected:

	template<std::size_t Index1, typename T, typename... Ts>
	std::enable_if_t<Index1 == sizeof...(Cs)>
		DoAction(const float elapsedMilliseconds,
			const ComponentMask& componentMask,
			const std::vector<uint32_t>& entityIds,
			T& t,
			Ts... ts);

	template<std::size_t Index1, typename T, typename... Ts>
	std::enable_if_t<Index1 != sizeof...(Cs)>
		DoAction(const float elapsedMilliseconds,
			const ComponentMask& componentMask,
			const std::vector<uint32_t>& entityIds,
			T& t,
			Ts... ts);

	virtual void DoAction(const float elapsedMilliseconds,
		Archetype* archetype) override;

	ECS& m_ecs;
	Func m_func;
	bool m_funcSet;
};

template<class... Cs>
System<Cs...>::System(ECS& ecs, const std::uint8_t& layer)
	:
	m_ecs(ecs),
	m_funcSet(false)
{
	m_ecs.RegisterSystem(layer, this);
}

template<class... Cs>
ComponentMask System<Cs...>::GetMask() const
{
	ComponentMask compMap;
	compMap.addComponents<Cs...>();
	return compMap;
}

template<class... Cs>
void System<Cs...>::Action(Func func)
{
	m_func = func;
	m_funcSet = true;
}

template<class... Cs>
void System<Cs...>::DoAction(const float elapsedMilliseconds, Archetype* archetype)
{
	if (m_funcSet)
		DoAction<0>(elapsedMilliseconds,
			archetype->componentMask,
			archetype->entityIds,
			archetype->componentData);
}

template<class... Cs>
template<std::size_t Index, typename T, typename... Ts>
std::enable_if_t<Index != sizeof...(Cs)>
System<Cs...>::DoAction(const float elapsedMilliseconds,
	const ComponentMask& componentMask,
	const std::vector<uint32_t>& entityIds,
	T& t,
	Ts... ts)
{
	using IthT = typename std::tuple_element<Index, std::tuple<Cs...>>::type;
	auto test = GetMask();
	auto index2 = 0;
	auto thisTypeCS = Component<IthT>::GetTypeID();
	index2 = std::popcount(componentMask.mask % (1 << (thisTypeCS)));

	if (index2 < 0 || index2 > std::popcount(componentMask.mask))
	{
		throw std::runtime_error
		("System was executed against an incorrect Archetype");
	}

	//auto tes = reinterpret_cast<IthT*>(&t[index2][0]));


	DoAction<Index + 1>(elapsedMilliseconds,
		componentMask,
		entityIds,
		t,
		ts...,
		reinterpret_cast<IthT*>(&t[index2][0]));
}

template<class... Cs>
template<std::size_t Index, typename T, typename... Ts>
std::enable_if_t<Index == sizeof...(Cs)>
System<Cs...>::DoAction(const float elapsedMilliseconds,
	const ComponentMask& componentMask,
	const std::vector<uint32_t>& entityIds,
	T& t,
	Ts... ts)
{
	m_func(elapsedMilliseconds, entityIds, ts...);
}
