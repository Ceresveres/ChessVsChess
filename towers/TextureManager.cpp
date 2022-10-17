#include "TextureManager.h"
#include <SDL_image.h>

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::loadTexture(std::string fileName, std::string id)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0)
	{
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect destRect{x, y, width, height};
	destRect.w = width;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopy(m_pRenderer, m_textureMap[id], NULL, &destRect);
	SDL_RenderDrawRect(m_pRenderer, &destRect);
}

void TextureManager::draw(std::string id, SDL_Rect rect) {
	SDL_RenderCopy(m_pRenderer, m_textureMap[id], NULL, &rect);
	SDL_RenderDrawRect(m_pRenderer, &rect);
}


void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Rect gridRect,  int currentRow, int currentFrame, SDL_RendererFlip flip)
{
	SDL_Rect destRect;
	gridRect.x = gridRect.w * currentFrame;
	gridRect.y = gridRect.h * (currentRow - 1);
	destRect.w = width;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(m_pRenderer, m_textureMap[id], &gridRect, &destRect, 0, 0, flip);
	draw(destRect);
}

void TextureManager::draw(std::string id, SDL_Rect gridRect, int currentRow, int currentFrame, SDL_RendererFlip flip)
{
	SDL_Rect destRect;
	destRect.w = 16;
	destRect.h = 16;
	destRect.x = 16 * currentFrame;
	destRect.y = 16 * currentRow;

	SDL_Rect tempRect = gridRect;
	tempRect.w = gridRect.w/2;
	tempRect.h = gridRect.h/2;
	for (int i = 0; i < 2; i++) {
		tempRect.x = gridRect.x + (gridRect.w / 2 * i);
		for (int j = 0; j < 2; j++) {

			tempRect.y = gridRect.y + (gridRect.h / 2 * j);

			SDL_RenderCopyEx(m_pRenderer, m_textureMap[id], &destRect, &tempRect, 0, 0, flip);
		}
	}
	//SDL_RenderCopyEx(m_pRenderer, m_textureMap[id], &destRect, &gridRect, 0, 0, flip);
	//draw(destRect);
}

void TextureManager::draw(SDL_Rect gridRect, int *color)
{
	SDL_SetRenderDrawColor(m_pRenderer, color[0], color[1], color[2], color[3]);
	SDL_RenderFillRect(m_pRenderer, &gridRect);
}

void TextureManager::draw(SDL_Rect gridRect)
{
	SDL_SetRenderDrawColor(m_pRenderer, 16, 10, 10, 255);
	SDL_RenderDrawRect(m_pRenderer, &gridRect);
}