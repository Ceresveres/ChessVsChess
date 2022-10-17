#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState) {
	gameStates.push_back(pState);
	gameStates.back()->onEnter();
}



void GameStateMachine::popState() {
	if (!gameStates.empty())
	{
		if (gameStates.back()->onExit())
		{
			delete gameStates.back();
			gameStates.pop_back();
		}
	}
}

void GameStateMachine::changeState(GameState* pState) {
	if (!gameStates.empty())
	{
		if (gameStates.back()->getStateID() == pState->getStateID())
		{
			return;
		}
		if (gameStates.back()->onExit())
		{
			delete gameStates.back();
			gameStates.pop_back();
		}
	}
	gameStates.push_back(pState);
	gameStates.back()->onEnter();
}

void GameStateMachine::update(Uint32 delta) {
	if (!gameStates.empty())
	{
		gameStates.back()->update(delta);
	}
}

void GameStateMachine::render() {
	if (!gameStates.empty())
	{
		gameStates.back()->render();
	}
}