#include <iostream>
#include "PlayState.h"
#include "Scene.h"
#include "PieceSystem.h"
#include "MapSystem.h"
#include "CollisionSystem.h"
#include "GraphicSystem.h"
const std::string PlayState::s_playID = "PLAY";

void PlayState::update(Uint32 delta)
{
	for (int i = 0; i < m_Scenes.size(); i++)
	{
		m_Scenes[i]->update(delta);
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_Scenes.size(); i++)
	{
		m_Scenes[i]->draw();
	}
}

bool PlayState::onEnter()
{

	auto objectManager = std::make_unique<ObjectManager>();
	auto scene = std::make_unique<Scene>(std::move(objectManager));
	std::unique_ptr<System> map = std::make_unique<Map>();
	scene->addSystem(std::move(map));
	std::unique_ptr<System> piece = std::make_unique<Piece>();
	scene->addSystem(std::move(piece));
	std::unique_ptr<System> collision = std::make_unique<CollisionSystem>();
	scene->addSystem(std::move(collision));
	std::unique_ptr<System> graphic = std::make_unique<GraphicSystem>();
	scene->addSystem(std::move(graphic));
	scene->init();

	m_Scenes.push_back(std::move(scene));
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_Scenes.size(); i++)
	{
		m_Scenes[i]->clean();
	}
	m_Scenes.clear();
	std::cout << "exiting PlayState\n";
	return true;
}