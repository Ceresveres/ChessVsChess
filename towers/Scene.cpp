#include "Scene.h"

const std::string Scene::s_sceneID = "Level_1";
static Scene* scene_ = nullptr;

Scene* Scene::GetSingleton() {
	if (scene_ == nullptr) {
		scene_ = new Scene();
	}
	return scene_;
}

void Scene::update(Uint32 delta) {
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->update();
	}
	moveBullet(delta);
	moveInvader(delta);
}

void Scene::draw(SDL_Renderer& pRenderer) {
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->draw(pRenderer);
	}
	for (auto const& var : bullets) {
		var->draw(pRenderer);
	}
	for (auto const& var : invaders) {
		var->draw(pRenderer);
	}
}

bool Scene::init() {
	Board* board{ Board::GetSingleton() };
	Store* store{ Store::GetSingleton() };
	board->scene = this;
	cout << "i";

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
	//for (auto& var : invaders) {
	//	var->update();
	//	if (var->pos.x < 0) delete (var);
	//	invaders.erase(&var);
	//}
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
		if ((*list)->getHP() <= 0) {
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