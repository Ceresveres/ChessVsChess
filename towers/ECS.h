#pragma once


#include "Component.h"
#include "Archetype.h"
#include "System.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <bit>
#include <bitset>

typedef std::vector<int> ArchetypeID;

struct Archetype;
class ComponentBase;
class ECS
{
private:
	typedef std::unordered_map<int, ComponentBase*>
		ComponentTypeIDBaseMap;

	struct Record
	{
		Archetype* archetype;
		std::size_t index;
	};

	typedef std::unordered_map<int, Record> EntityArchetypeMap;
	typedef std::unordered_map<int, ComponentMask> ComponentMasks;
	typedef std::vector<Archetype*> ArchetypesArray;

	typedef std::unordered_map<std::uint8_t, std::vector<SystemBase*>>
		SystemsArrayMap;

public:
	explicit ECS();

	~ECS();

	int GetNewID();

	template<class C>
	void RegisterComponent();

	template<class C>
	bool IsComponentRegistered();

	void RegisterSystem(const std::uint8_t& layer, SystemBase* system);

	void RegisterEntity(const uint32_t  entityId);

	void RunSystems(const std::uint8_t& layer, const float elapsedMilliseconds);

	Archetype* GetArchetype(const ComponentMask& compMask);

	template<class C, typename... Args>
	C* AddComponent(const uint32_t& entityId, Args&&... args);

	template<class C>
	void RemoveComponent(const uint32_t& entityId);

	template<class C>
	C* GetComponent(const uint32_t& entityId);

	template<class C>
	bool HasComponent(const uint32_t& entityId);

	bool HasEntity(const uint32_t& entityId);

	void RemoveEntity(const uint32_t& entityId);

	template<class... Cs>
	std::vector<int> GetEntitiesWith();

private:

	EntityArchetypeMap entityArchetypeMap;

	ArchetypesArray archetypes;

	int entityIdCounter;

	ComponentMasks componentMasks;

	SystemsArrayMap systems;

	ComponentTypeIDBaseMap componentMap;
};

template<class C>
void ECS::RegisterComponent()
{
	int componentTypeId = Component<C>::GetTypeID();

	if (componentMap.contains(componentTypeId))
		return; // can't re-register a type

	componentMap.emplace(componentTypeId, new Component<C>);
};

template<class C>
bool ECS::IsComponentRegistered() {
	int componentTypeId = Component<C>::GetTypeID();
	return (componentMap.contains(componentTypeId));
}

template<class C, typename... Args>
C* ECS::AddComponent(const uint32_t& entityId, Args&&... args) {
	// Get the component ID
	auto newComponentID = Component<C>::GetTypeID();
	if (componentMasks[entityId].hasComponent<C>()) { return nullptr; }

	Archetype* newArchetype = nullptr;
	C* newComponent = nullptr;

	componentMasks[entityId].addComponent<C>();

	Record& record = entityArchetypeMap[entityId];
	Archetype* oldArchetype = record.archetype;

	auto newComponentMask = componentMasks[entityId].mask;
	newArchetype = GetArchetype(componentMasks[entityId]);

	// if the entity already has components
	if (oldArchetype) {
		auto oldComponentMask = oldArchetype->componentMask.mask;
		auto ei = std::find(oldArchetype->entityIds.begin(), oldArchetype->entityIds.end() - 1, entityId);
		auto entityIndex = ei - oldArchetype->entityIds.begin();
		for (int i = std::popcount(newComponentMask) - 1, j = i - 1; newComponentMask > 0; --i) {
			auto ComponentID = std::bit_width(newComponentMask) - 1;

			const ComponentBase* const newComponentBase = componentMap[ComponentID];
			const std::size_t& newComponentDataSize = newComponentBase->GetSize();

			std::size_t currentSize = newArchetype->entityIds.size() * newComponentDataSize;
			std::size_t newSize = currentSize + newComponentDataSize;

			if (newSize > newArchetype->componentDataSize[i]) {
				newArchetype->componentDataSize[i] *= 2;
				newArchetype->componentDataSize[i] += newComponentDataSize;
				unsigned char* newData = new unsigned char[newArchetype->componentDataSize[i]];
				for (auto e = 0; e < newArchetype->entityIds.size(); ++e) {
					newComponentBase->MoveData(&newArchetype->componentData[i][e * newComponentDataSize],
						&newData[e * newComponentDataSize]);
					newComponentBase->DestroyData(&newArchetype->componentData[i][e * newComponentDataSize]);
				}
				delete[] newArchetype->componentData[i];
				newArchetype->componentData[i] = newData;
			}


			if (oldComponentMask & (1 << (std::bit_width(newComponentMask) - 1))) {
				const ComponentBase* const oldComponentBase = componentMap[ComponentID];
				const std::size_t& oldCompDataSize = oldComponentBase->GetSize();

				oldComponentBase->MoveData(&oldArchetype->componentData[j][entityIndex * oldCompDataSize],
					&newArchetype->componentData[i][currentSize]);

				oldComponentBase->DestroyData(&oldArchetype->componentData[j][entityIndex * oldCompDataSize]);
				j--;
			}
			else {
				newComponent
					= new (&newArchetype->componentData[i][currentSize])
					C(std::forward<Args>(args)...);
			}


			newComponentMask = (newComponentMask % std::bit_floor(newComponentMask));
		}

		if (!oldArchetype->entityIds.empty()) {
			auto lastEntity = oldArchetype->entityIds.size() - 1;

			for (int i = std::popcount(oldComponentMask) - 1; oldComponentMask > 0; --i) {
				auto ComponentID = std::bit_width(oldComponentMask) - 1;
				const ComponentBase* const oldComponentBase = componentMap[ComponentID];
				const std::size_t& oldComponentDataSize = oldComponentBase->GetSize();

				oldComponentBase->MoveData(&oldArchetype->componentData[i][lastEntity * oldComponentDataSize],
					&oldArchetype->componentData[i][entityIndex * oldComponentDataSize]);
				oldComponentBase->DestroyData(&oldArchetype->componentData[i][lastEntity * oldComponentDataSize]);

				oldComponentMask = (oldComponentMask % std::bit_floor(oldComponentMask));
			}
			std::swap(oldArchetype->entityIds[entityIndex], oldArchetype->entityIds[lastEntity]);
			oldArchetype->entityIds.pop_back();
		}
	}
	else
	{
		// Get size of component
		const ComponentBase* const newComponentBase = componentMap[newComponentID];
		const std::size_t& newComponentDataSize = newComponentBase->GetSize();

		std::size_t currentSize = newArchetype->entityIds.size() * newComponentDataSize;
		std::size_t newSize = currentSize + newComponentDataSize;

		// If new size is greater than what's allocated, reallocate
		if (newSize > newArchetype->componentDataSize[0]) {

			// Double the size and add component data size
			newArchetype->componentDataSize[0] *= 2;
			newArchetype->componentDataSize[0] += newComponentDataSize;
			unsigned char* newData = new unsigned char[newArchetype->componentDataSize[0]];

			for (auto e = 0; e < newArchetype->entityIds.size(); ++e) {
				newComponentBase->MoveData(&newArchetype->componentData[0][e * newComponentDataSize],
					&newData[e * newComponentDataSize]);
				newComponentBase->DestroyData(&newArchetype->componentData[0][e * newComponentDataSize]);
			}
			delete[](newArchetype->componentData[0]);

			newArchetype->componentData[0] = newData;
		}

		newComponent
			= new (&newArchetype->componentData[0][currentSize])
			C(std::forward<Args>(args)...);
	}

	newArchetype->entityIds.push_back(entityId);
	record.index = newArchetype->entityIds.size() - 1;
	record.archetype = newArchetype;

	return newComponent;
}

template<class C>
void ECS::RemoveComponent(const uint32_t& entityId) {
	if (!IsComponentRegistered<C>()) { return; };

	if (!componentMasks[entityId].hasComponent<C>()) { return; };

	Record& record = entityArchetypeMap[entityId];
	auto oldArchetype = record.archetype;
	auto oldComponentMask = oldArchetype->componentMask.mask;

	componentMasks[entityId].removeComponent<C>();

	auto newArchetype = GetArchetype(componentMasks[entityId]);
	auto newComponentMask = newArchetype->componentMask.mask;

	auto entityIndex = std::find(oldArchetype->entityIds.begin(), oldArchetype->entityIds.end() - 1, entityId) - oldArchetype->entityIds.begin();
	auto lastEntity = oldArchetype->entityIds.size() - 1;

	for (int j = std::popcount(oldComponentMask) - 1, i = j - 1; oldComponentMask > 0; --j) {
		auto ComponentID = std::bit_width(oldComponentMask) - 1;
		const ComponentBase* const newComponentBase = componentMap[ComponentID];
		const std::size_t& newComponentDataSize = newComponentBase->GetSize();
		std::size_t currentSize = newArchetype->entityIds.size() * newComponentDataSize;
		std::size_t newSize = currentSize + newComponentDataSize;

		if (newComponentMask & (1 << (std::bit_width(oldComponentMask) - 1))) {
			// Reallocate space for the newArchetype data size
			if (newSize > newArchetype->componentDataSize[i]) {
				newArchetype->componentDataSize[i] *= 2;
				newArchetype->componentDataSize[i] += newComponentDataSize;
				unsigned char* newData = new unsigned char[newArchetype->componentDataSize[i]];
				for (auto ei = 0; ei < newArchetype->entityIds.size(); ++ei) {
					newComponentBase->MoveData(&newArchetype->componentData[i][ei * newComponentDataSize],
						&newData[ei * newComponentDataSize]);
					newComponentBase->DestroyData(&newArchetype->componentData[i][ei * newComponentDataSize]);
				}
				delete[] newArchetype->componentData[i];
				newArchetype->componentData[i] = newData;
			}
			newComponentBase->MoveData(&oldArchetype->componentData[j][entityIndex * newComponentDataSize],
				&newArchetype->componentData[i][currentSize]);

			newComponentBase->MoveData(&oldArchetype->componentData[j][lastEntity * newComponentDataSize],
				&oldArchetype->componentData[j][entityIndex * newComponentDataSize]);

			newComponentBase->DestroyData(&oldArchetype->componentData[j][lastEntity * newComponentDataSize]);


			i--;

		}
		else {
			// Deletes the component data we're trying to remove
			newComponentBase->MoveData(&oldArchetype->componentData[j][lastEntity * newComponentDataSize],
				&oldArchetype->componentData[j][entityIndex * newComponentDataSize]);

			ComponentBase* removeWrapper = componentMap[ComponentID];
			removeWrapper->DestroyData(
				&oldArchetype->componentData[j][record.index * sizeof(C)]);
		}

		oldComponentMask = (oldComponentMask % std::bit_floor(oldComponentMask));

	}

	std::swap(oldArchetype->entityIds[entityIndex], oldArchetype->entityIds[lastEntity]);
	oldArchetype->entityIds.pop_back();

	newArchetype->entityIds.push_back(entityId);
	record.index = newArchetype->entityIds.size() - 1;
	record.archetype = newArchetype;
}


template<class C>
C* ECS::GetComponent(const uint32_t& entityId) {
	int compTypeId = Component<C>::GetTypeID();
	auto compSize = componentMap[compTypeId]->GetSize();

	Archetype* archetype = entityArchetypeMap[entityId].archetype;
	if (!archetype) { std::cout << "Entity not found\n"; return nullptr; };
	auto mask = componentMasks[entityId].mask;

	auto index = std::popcount(mask % (1 << (compTypeId)));

	auto e = std::find(archetype->entityIds.begin(), archetype->entityIds.end(), entityId);
	if (e == archetype->entityIds.end()) {
		std::cout << "Not found";
		return nullptr;
	}
	auto entityIndex = e - archetype->entityIds.begin();

	C* component = std::bit_cast<C*>(&archetype->componentData[index][entityIndex * compSize]);

	return component;
}

template<class C>
bool ECS::HasComponent(const uint32_t& entityId) {
	return (componentMasks[entityId]).hasComponent<C>();
}

template<class... Cs>
std::vector<int> ECS::GetEntitiesWith() {
	int newCompTypeId = Component<Cs...>::GetTypeID();
	std::vector<int> entities{};
	for (auto& [key, val] : entityArchetypeMap)
	{
		auto& iter = val.archetype->type;
		if (std::find(iter.begin(), iter.end(), newCompTypeId) != iter.end()) {
			entities.push_back(key);
		}
	}
	return entities;
}