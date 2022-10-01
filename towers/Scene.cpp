#include "Scene.h"

const std::string Scene::s_sceneID = "Level_1";
static Scene* scene_ = nullptr;

Scene* Scene::GetSingleton() {
	if (scene_ == nullptr) {
		scene_ = new Scene();
	}
	return scene_;
}

void Scene::update() {
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->update();
	}
	moveBullet();

}

void Scene::draw(SDL_Renderer& pRenderer) {
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->draw(pRenderer);
	}
	for (auto const& var : bullets) {
		var->draw(pRenderer);
	}
}

bool Scene::init() {
	Board* board{ Board::GetSingleton() };
	Store* store{ Store::GetSingleton() };
	m_Objects.push_back(board);
	m_Objects.push_back(store);
	addInvader(7, 2, BASIC);
	std::cout << "entering " << s_sceneID << "\n";
	return true;
}

void Scene::clean() {
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->clean();
	}
}


//Spawning logic for bullets/invaders will be moved
void Scene::addInvader(int x, int y, int type) {
	Board* board{ Board::GetSingleton() };
	if (x < 0 || x >= GRID_NUM_X || y < 0 || y >= GRID_NUM_Y) return;
	Invader* newInvader = nullptr;
	switch (type) {
	case BASIC:
		newInvader = new Invader(new LoaderParams(x, y, 50, 50));
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
		board->grid[x][y].addInvader(newInvader);
		invaders.push_back(newInvader);
	}
}

bool Scene::moveInvader() {
	for (auto& var : invaders) {
		var->update();
	}
	return false;
}

void Scene::clearInvader() {
	Board* board{ Board::GetSingleton() };
	Store* store{ Store::GetSingleton() };
	for (auto list = invaders.begin(); list != invaders.end();) {
		if ((*list)->getHP() <= 0) {
			board->grid[(*list)->getX()][(*list)->getY()].delInvader(*list);
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

void Scene::moveBullet() {
	Board* board{ Board::GetSingleton() };
	for (auto const& var : bullets) {
		var->update();
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