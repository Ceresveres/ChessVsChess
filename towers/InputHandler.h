#pragma once
#include <iostream>
#include <SDL.h>

class InputHandler
{
public:
	static InputHandler* GetSingleton();

	void update();
	//bool isKeyDown(SDL_Scancode key) { return (m_keystates) ? m_keystates[key] : false; };
	bool isKeyDown(SDL_Scancode key);
private:
	InputHandler();
	~InputHandler();
	const Uint8* m_keystates;
	static InputHandler* inputHandler_;
	void onKeyDown(SDL_Event event);
	
};
