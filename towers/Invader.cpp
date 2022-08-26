#include "Invader.h"
#include "Board.h"
#include "Game.h"

#include <iostream>
using namespace std;

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



void Invader::go(Board* board) {
	vector<Modifier*> modifiers{};
	for (int i = effects_.size()-1; i >= 0; i--) {
		if (effects_[i]->modifier != nullptr) {
			modifiers.push_back(effects_[i]->modifier);
		}
		effects_[i]->triggerEffect(*this);
	}
	for (int i = 0; i < modifiers.size(); i++) {
		switch(modifiers[i]->type) {
		case 0:
			counter += step - modifiers[i]->val;
			break;
		}
	}
	if (counter >= 10 * speed) {
		board->grid[x][y].delInvader(this);
		x--;
		board->grid[x][y].delInvader(this);
		counter = 0;
	}

	//if (!attacking) {
	//	if (slow) {
	//		counter += 5;
	//	}
	//	else {
	//		counter += 10;
	//	}
	//		
	//	if (counter >= 10 * speed) {
	//		board->grid[x][y].delInvader(this);
	//		x--;
	//		board->grid[x][y].delInvader(this);
	//		counter = 0;
	//	}
	//}
}

void Invader::printName() {
	//if (attacking) {
	//	PrintWithColor(name, FOREGROUND_GREEN);
	//} else if (burn) {
	//	PrintWithColor(name, FOREGROUND_RED | FOREGROUND_BLUE);
	//} else if (slow) {
	//	PrintWithColor(name, FOREGROUND_BLUE);
	//} else {
	//	PrintWithColor(name);
	//}
}

void Invader::printLife() {
	PrintWithColor(to_string(HP));
}

void Invader::hit(int damage) {
	HP -= damage;
	if (HP < 0) HP = 0;
}

bool Invader::move(Board* board) {
	//if (slow) {
	//	slowCounter++;
	//	if (slowCounter >= slowTime) {
	//		slow = false;
	//	}
	//}
	//
	//if (burn) {
	//	burnCounter++; 
	//	if ((burnCounter % burnTick) == 0) {
	//		board->grid[x][y].damageInvader(this, burnDamage);
	//	}
	//	if (burnCounter >= burnTime ) {
	//		burn = false;
	//	}
	//}
	//
	//if (!attacking) {
	//	if (slow) {
	//		counter += 5;
	//	}
	//	else {
	//		counter += 10;
	//	}
	//	
	//	if (counter >= 10 * speed) {
	//		board->grid[x][y].delInvader(this);
	//		x--;
	//		if (x < 0) return true;
	//		board->grid[x][y].addInvader(this);
	//		counter = 0;
	//	}
	//}
	//else {
	//	attackCounter++;
	//	if (attackCounter >= attackSpeed) {
	//		if (slow) { 
	//			board->grid[x][y].attackPiece(attack / 2); 
	//		} else { 
	//			board->grid[x][y].attackPiece(attack); 
	//		}
	//		attackCounter = 0;
	//	}
	//}
	//return false;
	return false;
}

bool Jumper::move(Board *board) {
	//if (hasJump && attacking) {
	//	board->grid[x][y].delInvader(this);
	//	x--;
	//	if (x < 0) return true;
	//	board->grid[x][y].addInvader(this);
	//	counter = 0;
	//	hasJump = false; attacking = false;
	//	return false;
	//}
	//else {
	//	return Invader::move(board);
	//}
	return false;
}

void Shield::hit(int damage) {
	HP -= damage;
	if (hasShield && HP <= shield) {
		boostAttributes();
	}
	else {
		if (HP < 0) HP = 0;
	}
}

void Shield::setSlow() {
	//if (hasShield) return;
	//else Invader::setSlow();
}
//
//void Shield::setBurn(int i) {
//	if (hasShield) return;
//	else Invader::setBurn(i);
//}

void Shield::printName() {
	//if (attacking) {
	//	PrintWithColor(name, FOREGROUND_GREEN);
	//}
	//else if (hasShield) {
	//	PrintWithColor(name, FOREGROUND_BLUE | FOREGROUND_GREEN);
	//}
	//else if (burn) {
	//	PrintWithColor(name, FOREGROUND_RED | FOREGROUND_BLUE);
	//}
	//else if (slow) {
	//	PrintWithColor(name, FOREGROUND_BLUE);
	//}
	//else {
	//	PrintWithColor(name);
	//}
}