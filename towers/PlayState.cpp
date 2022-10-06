#include <iostream>
#include "PlayState.h"
#include "Scene.h"
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
		m_Scenes[i]->draw(*m_renderer);
	}
}

bool PlayState::onEnter()
{
	Scene* scene{ Scene::GetSingleton(m_renderer) };
	m_Scenes.push_back(scene);
	std::cout << "entering PlayState\n";
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