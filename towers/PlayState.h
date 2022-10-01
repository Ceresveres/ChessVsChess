#pragma once
#include "GameState.h"
#include "Scene.h"
#include <vector>

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	PlayState(SDL_Renderer* rend)
		: m_renderer{ rend } {}
	virtual std::string getStateID() const { return s_playID; }
private:
	SDL_Renderer* m_renderer = NULL;
	static const string s_playID;
	std::vector<Scene*> m_Scenes;
};