#pragma once
#include "Object.h"
#include "Store.h"
#include "Board.h"
#include "Bullet.h"
#include "Piece.h"
#include "Invader.h"
#include "TextureManager.h"
#include <list>
#include <vector>
#include <SDL.h>

class Invader;
class Bullet;
class Piece;
class Scene;
class Scene {
	static const string s_sceneID;
	TextureManager* sTextureManager{ TextureManager::GetSingletonInstance() };
	std::vector<Object*> m_Objects;
	std::vector<MoveComponent*> m_Move = {};
	std::vector<Piece*> pieces = {};
	vector<Invader*> invaders = {};
	list<Bullet*> bullets = {};
	Scene()
	{
		init();
	}

	Scene(SDL_Renderer* rend) : m_renderer(rend)
	{
		init();
	}
public:

	static Scene* GetSingleton();
	static Scene* GetSingleton(SDL_Renderer* rend);
	SDL_Renderer* m_renderer = NULL;
	virtual std::string getStateID() const { return s_sceneID; }
	virtual void update(Uint32 delta);
	virtual bool init();
	virtual void clean();
	virtual void draw(SDL_Renderer& pRenderer);

	void addInvader(int x, int y, int type);
	void addPiece(int x, int y, int type);

	bool moveInvader(Uint32 delta);
	void clearInvader();

	void addBullet(Bullet* p);
	void moveBullet(Uint32 delta);
};

