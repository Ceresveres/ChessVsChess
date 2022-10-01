#pragma once
#include <vector>
#include"GameState.h"
using namespace std;

class GameStateMachine {
public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();
	void update();
	void render();

//private:
	vector<GameState*> m_gameStates;
};