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
	void drawFrame(std::string id, int x, int y, int width, int height, SDL_Rect gridRect, int currentRow, int currentFrame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTemp(SDL_Rect gridRect, int *color);
	void drawHitbox(SDL_Rect gridRect);
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
	std::map<std::string, SDL_Texture*> m_textureMap;
	SDL_Renderer* m_pRenderer = nullptr;
	static TextureManager* s_pInstance;
};