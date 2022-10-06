#include "TextureManager.h"
#include <SDL_image.h>

TextureManager* TextureManager::s_pInstance = 0;

//SDL_Texture* loadTexture(std::string path)
//{
//	//The final texture
//	SDL_Texture* newTexture = NULL;
//
//	//Load image at specified path
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (loadedSurface == NULL)
//	{
//		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//	}
//	else
//	{
//		//Create texture from surface pixels
//		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
//		if (newTexture == NULL)
//		{
//			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//		}
//
//		//Get rid of old loaded surface
//		SDL_FreeSurface(loadedSurface);
//	}
//
//	return newTexture;
//}


bool TextureManager::load(string fileName, string id)
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

void TextureManager::draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect dstRect {x, y, width, height};
	dstRect.w = width;
	dstRect.h = height;
	dstRect.x = x;
	dstRect.y = y;
	SDL_RenderCopy(m_pRenderer, m_textureMap[id], NULL, &dstRect);
	//SDL_RenderCopy(pRenderer, m_textureMap[id], NULL, NULL);

	//SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, NULL, NULL, flip);
}

void TextureManager::drawFrame(string id, int x, int y, int width, int height, SDL_Rect gridRect,  int currentRow, int currentFrame, SDL_RendererFlip flip)
{
	//SDL_Rect srcRect;
	SDL_Rect destRect;
	gridRect.x = gridRect.w * currentFrame;
	gridRect.y = gridRect.h * (currentRow - 1);
	destRect.w = width;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(m_pRenderer, m_textureMap[id], &gridRect, &destRect, 0, 0, flip);
}