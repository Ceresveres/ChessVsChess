#pragma once
#include "Object.h"
#include "Store.h"
#include "Board.h"
#include "Bullet.h"
#include "Invader.h"
#include <list>
#include <vector>
#include <SDL.h>

class Invader;
class Bullet;
class Scene;
class Scene {
	static const string s_sceneID;
	std::vector<Object*> m_Objects;

	vector<Invader*> invaders = {};
	list<Bullet*> bullets = {};
	Scene()
	{
		init();
	}

public:

	static Scene* GetSingleton();

	virtual std::string getStateID() const { return s_sceneID; }
	virtual void update();
	virtual bool init();
	virtual void clean();
	virtual void draw(SDL_Renderer& pRenderer);

	void addInvader(int x, int y, int type);
	bool moveInvader();
	void clearInvader();

	void addBullet(Bullet* p);
	void moveBullet();
};

