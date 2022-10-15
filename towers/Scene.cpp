#include "Scene.h"
#include <iostream>
#include <string>
#include "ObjectHandler.h"

//const std::string Scene::s_sceneID = "Level_1";
static Scene* scene_ = nullptr;

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
	player.addComponent(Motion(1));
	player.addComponent(StaticSprite("Pieces"));
	player.addComponent(BoundingBox(25, 225, 50, 50));
	auto enemy = createObject();
	enemy.addComponent(Position(625, 225));
	enemy.addComponent(Size(50, 50));
	enemy.addComponent(Motion(-1));
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