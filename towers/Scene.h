#pragma once
#include "Object.h"
#include "Store.h"
#include "Board.h"
#include "Bullet.h"
#include "Piece.h"
#include "Invader.h"
#include "EventBus.h"
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
	WorldBoundsComponent bounds{ 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT };
	TextureManager* sTextureManager{ TextureManager::GetSingletonInstance() };
	std::vector<Object*> m_Objects;
	std::vector<MoveComponent*> m_Move = {};
	std::vector<Piece*> pieces = {};
	std::map<std::type_index, Object*> objects;
	vector<Invader*> invaders = {};
	list<Bullet*> bullets = {};
	EventBus* eventBus = new EventBus();
	Scene()
	{
		init();
	}
public:

	static Scene* GetSingleton();
	EventBus* getEventBus() { return eventBus; }
	virtual std::string getStateID() const { return s_sceneID; }
	virtual void update(Uint32 delta);
	virtual bool init();
	virtual void clean();
	virtual void draw();

	void addInvader(int x, int y, int type);
	void addPiece(int x, int y, int type);

	bool moveInvader(Uint32 delta);
	void clearInvader();
	void onCollisionEvent(CollisionEvent* collision);
	void onSpawnEvent(SpawnEvent* spawn);
	void addBullet(Bullet* p);
	void moveBullet(Uint32 delta);
};

