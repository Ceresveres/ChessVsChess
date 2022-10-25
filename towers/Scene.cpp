#include "Scene.h"


//const std::string Scene::s_sceneID = "Level_1";

//Scene::Scene(std::unique_ptr<ObjectManager> objectManager) : objectManager(std::move(objectManager)) 
//{
//}

Scene::Scene() {};

//void Scene::onCollisionEvent(CollisionEvent* collision) {
//	std::cout << "it works\n";
//}


//ObjectHandler Scene::createObject() { 
//	//return { objectManager->createObject(), this }; 
//}



void Scene::update(Uint32 delta) {
	const float elapsedMilliseconds = delta;
	std::uint8_t t = 0;
	entityComponentSystem.RunSystems(t, elapsedMilliseconds);
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

	entityComponentSystem.RegisterComponent<Position>();
	entityComponentSystem.RegisterComponent<Randomness>();
	entityComponentSystem.RegisterComponent<Name>();
	entityComponentSystem.RegisterComponent<StaticSprite>();
	entityComponentSystem.RegisterComponent<Size>();

	Entity ent(entityComponentSystem);
	ent.Add<Position>({ 25, 225 });
	ent.Add<Size>({ 50, 50 });
	ent.Add<StaticSprite>({ "Pieces" });
	auto comp = entityComponentSystem.GetComponent<Position>(ent.GetID());

	//System<Position> tmpmovement(entityComponentSystem, 0);
	//this->movement = &tmpmovement;

	//movement->Action([](const float elapsedMilliseconds,
	//	const std::vector<uint32_t>& entities,
	//	Position* p
	//	)
	//	{
	//		for (std::size_t i = 0; i < entities.size(); ++i)
	//		{
	//			std::cout << i << " Entity -----------------\n"
	//				<< "P: (" << p[i].x << ',' << p[i].y << ")\n"
	//				<< std::endl;

	//			p[i].x += 1.f * (elapsedMilliseconds / 1000.f);
	//			p[i].y += 1.f * (elapsedMilliseconds / 1000.f);
	//		}
	//	});

	//System<Position, Size, StaticSprite> tmpdrawing(entityComponentSystem, 0);
	//this->drawing = &tmpdrawing;
	//drawing->Action([](const float elapsedMilliseconds,
	//	const std::vector<uint32_t>& entities,
	//	Position* p,
	//	Size* s,
	//	StaticSprite* st
	//	)
	//	{
	//		for (std::size_t i = 0; i < entities.size(); ++i)
	//		{
	//			TextureManager::GetSingletonInstance()->draw(st[i].textureID, p[i].x, p[i].y, s[i].width, s[i].height);
	//			std::cout << i << " Entity -----------------\n"
	//				<< "P: (" << p[i].x << ',' << p[i].y << ")\n"
	//				<< std::endl;

	//			p[i].x += 1.f * (elapsedMilliseconds / 1000.f);
	//			p[i].y += 1.f * (elapsedMilliseconds / 1000.f);
	//		}
	//	});

	newSystem<Position>(entityComponentSystem, 0);
	setAction<Position>(1);
	//std::shared_ptr<System<Position, Size, StaticSprite>> newdrawing;
	//newdrawing->Action([](const float elapsedMilliseconds,
	//	const std::vector<uint32_t>& entities,
	//	Position* p,
	//	Size* s,
	//	StaticSprite* st
	//	)
	//	{
	//		for (std::size_t i = 0; i < entities.size(); ++i)
	//		{
	//			TextureManager::GetSingletonInstance()->draw(st[i].textureID, p[i].x, p[i].y, s[i].width, s[i].height);
	//			std::cout << i << " Entity -----------------\n"
	//				<< "P: (" << p[i].x << ',' << p[i].y << ")\n"
	//				<< std::endl;

	//			p[i].x += 1.f * (elapsedMilliseconds / 1000.f);
	//			p[i].y += 1.f * (elapsedMilliseconds / 1000.f);
	//		}
	//	});
	std::uint8_t t = 0;
	entityComponentSystem.RunSystems(t, 1000);

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