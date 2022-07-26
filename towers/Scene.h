#pragma once
#include <memory>
#include "Component.h"
#include "ComponentHandler.h"
#include "ComponentManager.h"
#include "ComponentMap.h"
#include "Object.h"
#include "ObjectManager.h"
#include "EventBus.h"
#include "System.h"
#include "TextureManager.h"
#include <list>
#include <string>

#include <vector>
#include <SDL.h>

struct ObjectHandler;
class Scene {
public:
	explicit Scene(std::unique_ptr<ObjectManager> objectManager);

	void init();
	void update(Uint32 delta);
	void draw();
	ObjectHandler createObject();
	void destroyObject(Object object);
	void addSystem(std::unique_ptr<System> system);
	void updateEntityMask(Object const& object, ComponentMap oldMask);

	template <typename ComponentType>
	void addCustomComponentManager(std::unique_ptr<ComponentManager<ComponentType>> manager) {
		int family = GetComponentFamily<ComponentType>();
		if (family >= componentManagers.size()) {
			componentManagers.resize(family + 1);
		}
		componentManagers[family] = manager;
	}

	template <typename ComponentType>
	void addComponent(Object const& object, ComponentType&& component) {
		ComponentManager<ComponentType>* manager = getComponentManager<ComponentType>();
		manager->addComponent(object, component);

		ComponentMap oldMask = objectMap[object];
		objectMap[object].addComponent<ComponentType>();

		updateEntityMask(object, oldMask);
	}

	template <typename ComponentType>
	void removeComponent(Object const& object) {
		ComponentManager<ComponentType>* manager = getComponentManager<ComponentType>();
		ComponentHandler<ComponentType> component = manager->lookup(object);
		component.destroy();

		ComponentMap oldMask = objectMap[object];
		objectMap[object].removeComponent<ComponentType>();

		updateEntityMask(object, oldMask);
	}

	template <typename ComponentType, typename... Args>
	void unpack(Object e, ComponentHandler<ComponentType>& handle, ComponentHandler<Args> &... args) {
		typedef ComponentManager<ComponentType> ComponentManagerType;
		auto mgr = getComponentManager<ComponentType>();
		handle = ComponentHandler<ComponentType>(e, mgr->lookup(e), mgr);

		unpack<Args...>(e, args...);
	}

	template <typename ComponentType>
	void unpack(Object e, ComponentHandler<ComponentType>& handle) {
		typedef ComponentManager<ComponentType> ComponentManagerType;
		auto mgr = getComponentManager<ComponentType>();
		handle = ComponentHandler<ComponentType>(e, mgr->lookup(e), mgr);
	}

	template<typename ComponentType>
	void removeComponent(Object object, ComponentType&& component) {

	}
	std::unique_ptr<ObjectManager> objectManager;
	std::vector<std::unique_ptr<BaseComponentManager>> componentManagers;
	std::vector<std::unique_ptr<System>> systems;
	std::map<Object, ComponentMap> objectMap;
	void clean();

	template <typename ComponentType>
	ComponentManager<ComponentType>* getComponentManager() {
		int family = GetComponentFamily<ComponentType>();

		if (family >= componentManagers.size()) {
			componentManagers.resize(family + 1);
		}

		if (!componentManagers[family]) {
			componentManagers[family] = std::make_unique<ComponentManager<ComponentType>>();
		}

		return static_cast<ComponentManager<ComponentType> *>(componentManagers[family].get());
	}
};

