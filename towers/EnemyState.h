#pragma once
#include "GameState.h"
class EnemyState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_enemyID; }
private:
	static const std::string s_enemyID;
};