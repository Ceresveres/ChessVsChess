#pragma once

#include "TextureManager.h"


#include "ECS.h"
#include "System.h"
#include "Component.h"
#include "Entity.h"
#include <algorithm>
#include <iostream>
#include <vector>

class ECS;
class Scene {
public:
	typedef std::unordered_map<int, SystemBase*>
		SystemBaseSystemTypeBaseMap;

	void init();
	void update(Uint32 delta);
	void draw();
	Scene();
	ECS entityComponentSystem;
	System<Position> *movement;
	System<Position, Size, StaticSprite> *drawing;

	template<typename... Args>
	void newSystem(ECS& ecs, int num);

	SystemBaseSystemTypeBaseMap systemsMap;

	template<class... Args>
	void setAction(int a);
};

template<typename... Args>
void Scene::newSystem(ECS& ecs, int num) {
	systemsMap.emplace(1, new System<Args...>(ecs, num));
}

template<class... Args>
void Scene::setAction(int a) {
	System<Args...>* syst = dynamic_cast<System<Args...>*>(systemsMap[a]);
	syst->Action([](const float elapsedMilliseconds,
		const std::vector<uint32_t>& entities,
		Position* p
		)
		{
			for (std::size_t i = 0; i < entities.size(); ++i)
			{
				std::cout << i << " Entity -----------------\n"
					<< "P: (" << p[i].x << ',' << p[i].y << ")\n"
					<< std::endl;

				p[i].x += 1.f * (elapsedMilliseconds / 1000.f);
				p[i].y += 1.f * (elapsedMilliseconds / 1000.f);
			}
		});
}