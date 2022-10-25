#include "Scene.h"
#include <iostream>
#include <string>

//const std::string Scene::s_sceneID = "Level_1";

//Scene::Scene(std::unique_ptr<ObjectManager> objectManager) : objectManager(std::move(objectManager)) 
//{
//}

Scene::Scene() : entityComponentSystem() {};

//void Scene::onCollisionEvent(CollisionEvent* collision) {
//	std::cout << "it works\n";
//}


//ObjectHandler Scene::createObject() { 
//	//return { objectManager->createObject(), this }; 
//}



void Scene::update(Uint32 delta) {
	//for (auto& system : systems) {
	//	system->update();
	//}
}

void Scene::draw() {
	//for (auto& system : systems) {
	//	system->draw();
	//}
}

void Scene::init() {
	//eventBus->subscribe(this, &Scene::onCollisionEvent);
	//eventBus->subscribe(this, &Scene::onSpawnEvent);

	//for (auto& system : systems) {
	//	system->init();
	//}
	auto textureManager = TextureManager::GetSingletonInstance();
	textureManager->loadTexture("assets/Icon01.png", "Pieces");
	textureManager->loadTexture("assets/tileset.png", "tileset");
	ECS ecs;
	entityComponentSystem.RegisterComponent<Position>();
	entityComponentSystem.RegisterComponent<Randomness>();
	entityComponentSystem.RegisterComponent<Name>();
	Entity ent(entityComponentSystem);
	//Entity entt(entityComponentSystem);
	//Entity enttt(entityComponentSystem);

	////ecs.AddComponent<Position>(ent.GetID());
	////ecs.AddComponent<Randomness>(ent.GetID());
	//ent.Add<Position>({ 10, 10 });
	//ent.Add<Randomness>({ 110 });
	//ent.Add<Name>({ "Billy Bob" });
	//ent.Add<test1>({ "Bilfly Bob" });
	//ent.Add<test2>({ "Bilfly Bob" });
	//ent.Add<test3>({ "Bilfly Bob" });
	//entt.Add<test1>({ "Bilfly Bob" });
	//entt.Add<Name>({ "Billy Bob" });
	//enttt.Add<Name>({ "Billy Bob" });


	////ent.Add<Randomness>({10});
	////ecs.RemoveComponent<Randomness>(ent.GetID());
	//auto componentt = entityComponentSystem->GetComponent<Randomness>(ent.GetID());
	//auto component = entityComponentSystem->GetComponent<Position>(ent.GetID());
	//auto componenttt = entityComponentSystem->GetComponent<Name>(ent.GetID());

	//entityComponentSystem->RemoveComponent<Name>(ent.GetID());
	//// auto componentttt = ecs.GetComponent<Name>(ent.GetID());
	//// ecs.RemoveComponent<Name>(ent.GetID());
	//auto vec = entityComponentSystem->GetEntitiesWith<Name>();
	//for (auto en : vec) {
	//	entityComponentSystem->RemoveEntity(en);
	//	//ecs.RemoveComponent<Position>(en);
	//	std::cout << en;
	//}
	//auto vec2 = entityComponentSystem->GetEntitiesWith<Position>();
	//for (auto en : vec2) {
	//	std::cout << std::endl << en;
	//}
	//for (int i = 0; i < 9; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		auto box = createObject();
	//		box.addComponent(BoundingBox(i*100, j*100, 100, 100));
	//		box.addComponent(Layer(1));
	//		if ((i + j) % 2) {
	//			box.addComponent(StaticSprite("tileset", 4, 1));
	//		}
	//		else {
	//			box.addComponent(StaticSprite("tileset", 4, 7));
	//		}

	//	}
	//}

	//auto player = createObject();
	//player.addComponent(Motion(1));
	//player.addComponent(Layer(7));
	//player.addComponent(StaticSprite("Pieces"));
	//player.addComponent(BoundingBox(25, 225, 50, 50));

	//auto enemy = createObject();
	//enemy.addComponent(Motion(-1));
	//enemy.addComponent(Layer(4));
	//enemy.addComponent(StaticSprite("Pieces"));
	//enemy.addComponent(BoundingBox(625, 225, 50, 50));
}

//
//
//void Scene::addSystem(std::unique_ptr<System> system) {
//	//system->registerScene(this);
//	//systems.push_back(std::move(system));
//}
//
//void Scene::clean() {
//
//}
//
//void Scene::updateEntityMask(Object const& object, ComponentMap oldComponentMap) {
//	//ComponentMap newComponentMap = objectMaps[object];
//
//	//for (auto& system : systems) {
//	//	ComponentMap systemSignature = system->getSignature();
//	//	if (newComponentMap.isNewMatch(oldComponentMap, systemSignature)) {
//	//		system->registerObject(object);
//	//	}
//	//	else if (newComponentMap.isNoLongerMatched(oldComponentMap, systemSignature)) {
//	//		system->unRegisterObject(object);
//	//	}
//	//}
//}
//
//void Scene::onSpawnEvent(SpawnEvent* spawn) {
//	//destroyObject(spawn->object);
//	//std::cout << "it works\n";
//}