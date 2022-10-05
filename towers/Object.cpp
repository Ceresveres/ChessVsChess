#include "Object.h"

Object::Object(const LoaderParams* pParams)
{
	mWidth = pParams->getWidth();
	mHeight = pParams->getHeight();
}

void Object::load(const LoaderParams* pParams)
{
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
