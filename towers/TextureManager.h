#pragma once

#include <iostream>
#include <map>
#include <SDL.h>
#include <string>
class TextureManager
{
public:
	bool loadTexture(std::string fileName, std::string id);
	void draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(std::string id, SDL_Rect rect);
	void draw(std::string id, SDL_Rect gridRect, int currentRow, int currentFrame, SDL_RendererFlip flip= SDL_FLIP_NONE);
	void draw(std::string id, int x, int y, int width, int height, SDL_Rect gridRect, int currentRow, int currentFrame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(SDL_Rect gridRect, int *color);
	void draw(SDL_Rect gridRect);

	static TextureManager* GetSingletonInstance()
	{
		if (instance == 0)
		{
			instance = new TextureManager();
			return instance;
		}
		return instance;
	}

	static TextureManager* GetSingleton(SDL_Renderer* renderer)
	{
		if (instance == 0)
		{
			instance = new TextureManager(renderer);
			return instance;
		}
		return instance;
	}

private:
	TextureManager() {}
	TextureManager(SDL_Renderer* renderer) : renderer(renderer) {}
	std::map<std::string, SDL_Texture*> textureMap;
	SDL_Renderer* renderer = nullptr;
	static TextureManager* instance;
};