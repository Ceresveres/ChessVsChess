#pragma once
#include <vector>
#include"GameState.h"

class GameStateMachine {
public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();
	void update(Uint32 delta);
	void render();

//private:
	std::vector<GameState*> gameStates;
};