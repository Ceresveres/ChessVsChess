#pragma once

#include<string>
#include <SDL_stdinc.h>
class GameState
{
	static const std::string s_menuID;
public:
	virtual void update(Uint32 delta) = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getStateID() const { return s_menuID; };
};