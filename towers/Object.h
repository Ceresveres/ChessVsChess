#pragma once
#include <string>
#include <SDL.h>

using namespace std;

struct PositionComponent
{
	int x, y;
	PositionComponent(int x, int y)
		: x(x), y(y) {}
	PositionComponent() = default;
};

class LoaderParams;
class Object
{
public:
	virtual void load(const LoaderParams* pParams);
	virtual void draw(SDL_Renderer& pRenderer);
	virtual void update();
	virtual void clean();
	//int getX() const { return mX; }
	//int getY() const { return mY; }
protected:
	Object(const LoaderParams* pParams);
	//PositionComponent pos;
	//int mX{};
	//int mY{};
	int mWidth{ 50 };
	int mHeight{ 50 };
};

class Object;
class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height)
	{
	}
	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTextureID() const { return m_textureID; }
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	std::string m_textureID;
};


