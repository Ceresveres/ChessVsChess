#include "Scene.h"
#include <iostream>
#include <string>
#include "ObjectHandler.h"

//const std::string Scene::s_sceneID = "Level_1";

Scene::Scene(std::unique_ptr<ObjectManager> objectManager) : objectManager(std::move(objectManager)) 
{
}

void Scene::onCollisionEvent(CollisionEvent* collision) {
	std::cout << "it works\n";
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
	eventBus->subscribe(this, &Scene::onCollisionEvent);
	for (auto& system : systems) {
		system->init();
	}
	auto textureManager = TextureManager::GetSingletonInstance();
	textureManager->loadTexture("assets/Icon01.png", "Pieces");
	textureManager->loadTexture("assets/tileset.png", "tileset");

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			auto box = createObject();
			box.addComponent(BoundingBox(i*100, j*100, 100, 100));
			box.addComponent(Layer(1));
			if ((i + j) % 2) {
				box.addComponent(StaticSprite("tileset", 4, 1));
			}
			else {
				box.addComponent(StaticSprite("tileset", 4, 7));
			}

		}
	}

	auto player = createObject();
	player.addComponent(Motion(1));
	player.addComponent(Layer(7));
	player.addComponent(StaticSprite("Pieces"));
	player.addComponent(BoundingBox(25, 225, 50, 50));

	auto enemy = createObject();
	enemy.addComponent(Motion(-1));
	enemy.addComponent(Layer(4));
	enemy.addComponent(StaticSprite("Pieces"));
	enemy.addComponent(BoundingBox(625, 225, 50, 50));
}

void Scene::destroyObject(Object object) {
	for (auto& system : systems) {
		system->unRegisterObject(object);
	}
	objectManager->destroyObject(object);
}

void Scene::addSystem(std::unique_ptr<System> system) {
	system->registerScene(this);
	systems.push_back(std::move(system));
}

void Scene::clean() {

}

void Scene::updateEntityMask(Object const& object, ComponentMap oldComponentMap) {
	ComponentMap newComponentMap = objectMaps[object];

	for (auto& system : systems) {
		ComponentMap systemSignature = system->getSignature();
		if (newComponentMap.isNewMatch(oldComponentMap, systemSignature)) {
			system->registerObject(object);
		}
		else if (newComponentMap.isNoLongerMatched(oldComponentMap, systemSignature)) {
			system->unRegisterObject(object);
		}
	}
}