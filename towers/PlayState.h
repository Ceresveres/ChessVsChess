#pragma once
#include "GameState.h"
#include "Scene.h"
#include <vector>
#include "TextureManager.h"

class PlayState : public GameState
{
public:
	virtual void update(Uint32 delta);
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	PlayState(TextureManager* textureManager)
		: m_TextureManager{ textureManager } {}
	virtual std::string getStateID() const { return s_playID; }
private:
	TextureManager* m_TextureManager = NULL;
	static const string s_playID;
	std::vector<std::unique_ptr<Scene>> m_Scenes;
};