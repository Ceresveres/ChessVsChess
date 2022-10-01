#include "Invader.h"
#include "Board.h"
#include "Game.h"

#include <iostream>
using namespace std;
Invader::Invader(const LoaderParams* pParams) : Object(pParams)
{
}

void Effect::initEffect(int type) {
	switch (type) {
	case 2:
		duration = 20;
		modifier = new Modifier(0, 5);
		break;
	case 1:
		duration = 30;
		tick = 3;
		damage = 11;
		break;
	case 0:
	default:
		break;
	}
}

int Effect::triggerEffect(Invader& invader) {
	duration--;
	if ((duration % tick) == 0) {
		invader.hit(damage);
	}
	if (duration <= 0) {
		invader.removeEffect(this);
	}
	return type;
}

void Invader::removeEffect(Effect* effect) {
	effects_.erase(remove(effects_.begin(), effects_.end(), effect), effects_.end());
}

void Invader::load(const LoaderParams* pParams)
{
	Object::load(pParams);
}

void Invader::update() {
	Board* board = Board::GetSingleton();
	vector<Modifier*> modifiers{};
	for (int i = (int)effects_.size() - 1; i >= 0; i--) {
		if (effects_[i]->modifier != nullptr) {
			modifiers.push_back(effects_[i]->modifier);
		}
		effects_[i]->triggerEffect(*this);
	}
	if (!attacking) {
		for (int i = 0; i < modifiers.size(); i++) {
			switch (modifiers[i]->type) {
			case 0:
				counter += step - modifiers[i]->val;
				break;
			}
		}
		if (modifiers.size() == 0) {
			counter += step;
		}
		if (counter >= 1000000 * speed) {
			board->grid[mX][mY].delInvader(this);
			mX--;
			if (mX < 0) return;
			board->grid[mX][mY].addInvader(this);
			counter = 0;
		}
	}
	else {
		attackCounter++;
		if (attackCounter >= attackSpeed) {
			board->grid[mX][mY].attackPiece(attack);
			attackCounter = 0;
		}
	}
	return;
}

void Invader::draw(SDL_Renderer& pRenderer) {
	SDL_Rect gridRect = { mX * (GRID_HEIGHT) + (mWidth/2),  mY * (GRID_WIDTH) + (mHeight/2), mWidth, mHeight };
	SDL_SetRenderDrawColor(&pRenderer, 100, 0, 50, 255);
	SDL_RenderFillRect(&pRenderer, &gridRect);
}

void Invader::hit(int damage) {
	HP -= damage;
	if (HP < 0) HP = 0;
}

//void Shield::hit(int damage) {
//	HP -= damage;
//	if (hasShield && HP <= shield) {
//		boostAttributes();
//	}
//	else {
//		if (HP < 0) HP = 0;
//	}
//}
