#include "Scene.h"

const std::string Scene::s_sceneID = "Level_1";
static Scene* scene_ = nullptr;

Scene* Scene::GetSingleton() {
	if (scene_ == nullptr) {
		scene_ = new Scene();
	}
	return scene_;
}

//Scene* Scene::GetSingleton(SDL_Renderer* rend) {
//	if (scene_ == nullptr) {
//		scene_ = new Scene(rend);
//	}
//	return scene_;
//}

template<class Movable>
void UpdatePosition(Uint32 deltaTime, Movable& go, WorldBoundsComponent& bounds)
{
	go.move.UpdatePosition(deltaTime, go.pos, bounds);
}

void Scene::update(Uint32 delta) {
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->update();
	}
	//for (auto const& var : m_Move) {
	//	var->UpdatePosition(delta);
	//}
	//for (auto& go : this->m_Move)
	//{
	//	UpdatePosition(delta, go, this->bounds);
	//}
	moveBullet(delta);
	moveInvader(delta);
}

void Scene::draw() {
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->draw();
	}
	for (auto const& var : bullets) {
		var->draw();
	}
	for (auto const& var : invaders) {
		var->draw();
	}
}

void Scene::onCollisionEvent(CollisionEvent* collision) {
	cout << "it works\n";
}

void Scene::onSpawnEvent(SpawnEvent* spawn) {
	m_Objects.push_back(spawn->ObjectA);
}

bool Scene::init() {
	eventBus->subscribe(this, &Scene::onSpawnEvent);
	Board* board{ Board::GetSingleton() };
	Store* store{ Store::GetSingleton() };
	board->SetEventBus(eventBus);
	cout << "i";
	sTextureManager->loadTexture("assets/Icon01.png", "Icon");
	sTextureManager->loadTexture("assets/skull.png", "Pieces");

	m_Objects.push_back(board);
	m_Objects.push_back(store);
	addInvader(8, 2, BASIC);
	std::cout << "entering " << s_sceneID << "\n";
	return true;
}

void Scene::clean() {
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->clean();
	}
}

void Scene::addPiece(int x, int y, int type) {


}

//Spawning logic for bullets/invaders will be moved
void Scene::addInvader(int x, int y, int type) {
	Board* board{ Board::GetSingleton() };
	if (x < 0 || x >= GRID_NUM_X || y < 0 || y >= GRID_NUM_Y) return;
	Invader* newInvader = nullptr;
	switch (type) {
	case BASIC:
		newInvader = new Invader((x*100)+25, (y*100)+25);
		break;
	case JUMPER:
		//newInvader = new Jumper();
		break;
	case HEAVY:
		//newInvader = new Heavy();
		break;
	case SHIELD:
		//newInvader = new Shield();
		break;
	default:
		break;
	}
	if (newInvader != nullptr) {
		board->addInvader(x, y, newInvader);
		invaders.push_back(newInvader);
	}
}

bool Scene::moveInvader(Uint32 delta) {
	for (auto const& var : invaders) {
		var->update(delta);
	}
	for (auto list = invaders.begin(); list != invaders.end();) {
		(*list)->update(delta);
		if ((*list)->pos.x % 300 == 0) {
			cout << "hi";
		}
		if ((*list)->pos.x <= -50) {
			delete (*list);
			list = invaders.erase(list);
		}
		else {
			list++;
		}
	}
	return false;
}

void Scene::clearInvader() {
	Board* board{ Board::GetSingleton() };
	Store* store{ Store::GetSingleton() };
	for (auto list = invaders.begin(); list != invaders.end();) {
		if ((*list)->health.getHP() <= 0) {
			board->grid[(*list)->pos.x][(*list)->pos.y].delInvader(*list);
			store->addMoney((*list)->getReward());
			delete (*list);
			list = invaders.erase(list);
		}
		else {
			list++;
		}
	}
}

void Scene::addBullet(Bullet* p) {
	bullets.push_back(p);
}

void Scene::moveBullet(Uint32 delta) {
	Board* board{ Board::GetSingleton() };
	for (auto const& var : bullets) {
		var->update(delta);
	}

	for (auto list = bullets.begin(); list != bullets.end(); ) {
		if ((*list)->hit) {
			delete* list;
			list = bullets.erase(list);
		}
		else {
			list++;
		}
	}
}

//***************************************
// To be refactor into appropriate object classes
//***************************************
//void Game::makeInvaders() {
//	makeCounter++;
//	if (makeCounter >= makeSpeed) {
//		addInvader(GRID_NUM_X - 1, RANDOM(GRID_NUM_Y), RANDOM(SHIELD+1));
//		makeCounter = 0;
//	}
//}