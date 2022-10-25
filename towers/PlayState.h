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
		: textureManager{ textureManager } {}
	virtual std::string getStateID() const { return playID; }
private:
	TextureManager* textureManager = NULL;
	static const std::string playID;
	std::vector<Scene*> scenes;
};