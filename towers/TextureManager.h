#pragma once

#include <iostream>
#include <map>
#include <SDL.h>
using namespace std;
class TextureManager
{
public:
	bool load(string fileName, std::string id);
	void draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(string id, int x, int y, int width, int height, SDL_Rect gridRect, int currentRow, int currentFrame, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static TextureManager* GetSingletonInstance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	static TextureManager* GetSingleton(SDL_Renderer* renderer)
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager(renderer);
			return s_pInstance;
		}
		return s_pInstance;
	}

private:
	TextureManager() {}
	TextureManager(SDL_Renderer* renderer) : m_pRenderer(renderer) {}
	map<string, SDL_Texture*> m_textureMap;
	SDL_Renderer* m_pRenderer = nullptr;
	static TextureManager* s_pInstance;
};