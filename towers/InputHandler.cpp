#include <iostream>
#include "InputHandler.h"
//#include "Game.h"

InputHandler* InputHandler::inputHandler = nullptr;

void InputHandler::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;
		default:
			break;
		}
	}
}

void InputHandler::onKeyDown(SDL_Event event) {
	keystates = SDL_GetKeyboardState(0);
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
	if (keystates != 0)
	{
		if (keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

InputHandler* InputHandler::GetSingleton() {
	if (inputHandler == nullptr)
	{
		inputHandler = new InputHandler();
	}
	return inputHandler;
}

InputHandler::InputHandler() {

}