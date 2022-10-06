#pragma once
#include <string>
#include <SDL.h>
#include <cmath>
#include "TextureManager.h"
#include <vector>
#include <SDL_image.h>
//#include <list>


using namespace std;

struct PositionComponent
{
	int x, y;
	PositionComponent(int x, int y)
		: x(x), y(y) {}
	PositionComponent() = default;
};

//struct GraphicComponent
//{
//	float colorR, colorG, colorB;
//	int spriteIndex;
//	int scale;
//	SDL_Texture* texture;
//	GraphicComponent(float colorR, float colorG, float colorB, int spriteIndex, int scale)
//		: colorR(colorR)
//		, colorG(colorG)
//		, colorB(colorB)
//		, spriteIndex(spriteIndex)
//		, scale(scale)
//	{
//	}
//};
struct DynamicComponent {
	string mTextureID;
	int m_currentRow{1};
	int m_currentFrame{ 0 };
	SDL_RendererFlip m_flip;
	SDL_Rect gridRect = { 0,  0, 16, 16 };
	DynamicComponent(std::string texture, SDL_RendererFlip flip = SDL_FLIP_NONE)
		: mTextureID(texture), m_flip(flip) {}
	void draw(PositionComponent& pos, int width, int height) {
		m_currentFrame = int(((SDL_GetTicks() / 100) % 4));
		TextureManager::GetSingletonInstance()->drawFrame(mTextureID, pos.x, pos.y, width, height, gridRect, m_currentRow, m_currentFrame, m_flip);
	}
};

struct StaticComponent {
	string mTextureID;
	StaticComponent(std::string texture)
	: mTextureID(texture) {}
	//TextureManager::GetSingletonInstance()->draw("Icon", pos.x, pos.y, mWidth, mHeight, &pRenderer);
	void draw(PositionComponent& pos, int mWidth, int mHeight) {
		TextureManager::GetSingletonInstance()->draw(mTextureID, pos.x, pos.y, mWidth, mHeight);
	}

};

struct MoveComponent
{
    float velx, vely;
    float fracx, fracy;
	int x, y;
	MoveComponent(int x, int y, float speed) : x(x), y(y), fracx{ 0 }, fracy{ 0 }, velx(speed), vely(0)
    {   }

    void UpdatePosition(Uint32 delta, PositionComponent& pos)
    {
        // update position based on movement velocity & delta time
        float intX, intY;
        fracx = modf((velx * (float)(delta / 100.0)) + fracx, &intX);
        pos.x += (int)intX;
        fracy = modf((vely * (float)(delta / 100.0)) + fracy, &intY);
        pos.y += (int)intY;
    }

	void UpdatePosition(Uint32 delta)
	{
		// update position based on movement velocity & delta time
		float intX, intY;
		fracx = modf((velx * (float)(delta / 100.0)) + fracx, &intX);
		x += (int)intX;
		fracy = modf((vely * (float)(delta / 100.0)) + fracy, &intY);
		y += (int)intY;
	}
};


class LoaderParams;
class Object
{
public:
	virtual void load(const LoaderParams* pParams);
	virtual void draw(SDL_Renderer& pRenderer);
	virtual void update();
	virtual void clean();
protected:
	Object(const LoaderParams* pParams);
	int mWidth{ 50 };
	int mHeight{ 50 };
};

class Object;
class LoaderParams
{
public:
	LoaderParams(int width, int height) : m_width(width), m_height(height)
	{
	}
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTextureID() const { return m_textureID; }
private:
	int m_width;
	int m_height;
	std::string m_textureID;
};




