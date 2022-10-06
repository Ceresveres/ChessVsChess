#pragma once
#include <string>
#include <SDL.h>
#include <cmath>
#include "TextureManager.h"
#include <vector>
#include <SDL_image.h>

using namespace std;

struct PositionComponent
{
	int x, y;
	PositionComponent(int x, int y)
		: x(x), y(y) {}
	PositionComponent() = default;
};

struct SpawnComponent {
	
};

struct HealthComponent
{
	int HP;
	HealthComponent(int HP) : HP(HP) {};
	int getHP() { return HP; };
	void hit(int damage) {
		HP -= damage;
		if (HP < 0) HP = 0;
	}
};

struct SizeComponent
{
	int mWidth, mHeight;
	SizeComponent(int width, int height)
		: mWidth(width), mHeight(height) {}
	SizeComponent() = default;
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
	void draw(PositionComponent& pos, SizeComponent& size) {
		m_currentFrame = int(((SDL_GetTicks() / 500) % 4));
		TextureManager::GetSingletonInstance()->drawFrame(mTextureID, pos.x, pos.y, size.mWidth, size.mHeight, gridRect, m_currentRow, m_currentFrame, m_flip);
	}
};

struct StaticComponent {
	string mTextureID;
	StaticComponent(std::string texture)
	: mTextureID(texture) {}
	void draw(PositionComponent& pos, SizeComponent& size) {
		TextureManager::GetSingletonInstance()->draw(mTextureID, pos.x, pos.y, size.mWidth, size.mHeight);
	}
};

struct MoveComponent
{
    float velx, vely;
	float fracx = 0;
	float fracy = 0;
	MoveComponent(float speed) : velx(speed), vely(0)
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
};

class Object
{
public:
	virtual void update();
	virtual void draw();
	virtual void clean();
protected:
	Object() {};
};





