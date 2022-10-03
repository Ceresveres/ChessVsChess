#include "Object.h"

Object::Object(const LoaderParams* pParams)
{
	//mX = pParams->getX();
	//PositionComponent *pos = new PositionComponent( pParams->getX(), pParams->getY() );
	//mY = pParams->getY();
	mWidth = pParams->getWidth();
	mHeight = pParams->getHeight();
}

void Object::load(const LoaderParams* pParams)
{
	//mX = pParams->getX();
	//mY = pParams->getY();
	mWidth = pParams->getWidth();
	mHeight = pParams->getHeight();
}

void Object::draw(SDL_Renderer& pRenderer)
{
}

void Object::update()
{
}

void Object::clean()
{
}
