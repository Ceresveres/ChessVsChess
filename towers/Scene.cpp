#include "Scene.h"
#include <iostream>
#include <string>
#include "ObjectHandler.h"

//const std::string Scene::s_sceneID = "Level_1";
static Scene* scene_ = nullptr;

Scene::Scene(std::unique_ptr<ObjectManager> objectManager) : objectManager(std::move(objectManager)) 
{
}


ObjectHandler Scene::createObject() { 
	return { objectManager->createObject(), this }; 
}

void Scene::update(Uint32 delta) {
	for (auto& system : systems) {
		system->update();
	}
}

void Scene::draw() {
	for (auto& system : systems) {
		system->draw();
	}
}



void Scene::init() {
	for (auto& system : systems) {
		system->init();
	}
	auto sTextureManager = TextureManager::GetSingletonInstance();
	sTextureManager->loadTexture("assets/Icon01.png", "Pieces");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			auto box = createObject();
			box.addComponent(Grid(i*100, j*100));
		}
	}
	auto player = createObject();
	player.addComponent(Position(25, 225));
	player.addComponent(Size(50, 50));
	player.addComponent(StaticSprite("Pieces"));
}

void Scene::destroyObject(Object object) {

}

void Scene::addSystem(std::unique_ptr<System> system) {
	system->registerScene(this);
	systems.push_back(std::move(system));
}

void Scene::clean() {

}

void Scene::updateEntityMask(Object const& object, ComponentMap oldMask) {
	ComponentMap newMask = objectMap[object];

	for (auto& system : systems) {
		ComponentMap systemSignature = system->getSignature();
		if (newMask.isNewMatch(oldMask, systemSignature)) {
			system->registerObject(object);
		}
		else if (newMask.isNoLongerMatched(oldMask, systemSignature)) {
			system->unRegisterObject(object);
		}
	}
}