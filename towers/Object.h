#pragma once
#include <string>
#include <SDL.h>
#include "ui-tools.h"
#include <cmath>
#include <vector>
#include <list>


using namespace std;

struct PositionComponent
{
	int x, y;
	PositionComponent(int x, int y)
		: x(x), y(y) {}
	PositionComponent() = default;
};



struct MoveComponent
{
    float velx, vely;
    float fracx, fracy;

	MoveComponent(float speed) : fracx{ 0 }, fracy{ 0 }, velx(speed), vely(0)
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


