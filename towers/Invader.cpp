#include "Invader.h"
#include "Board.h"
#include "Game.h"

#include <iostream>
using namespace std;

bool Invader::move(Board& board) {
	if (slow) {
		slowCounter++;
		if (slowCounter >= 10) {
			slow = false;
		}
	}
	if (!attacking) {
		if (slow) {
			counter += 1;
		}
		else {
			counter += 10;
		}
		
		if (counter >= 10 * speed) {
			board.grid[x][y].delInvader(this);
			x--;
			if (x < 0) return true;
			board.grid[x][y].addInvader(this);
			counter = 0;
		}
	}
	else {
		board.grid[x][y].attackPiece(attack);
	}
	return false;
}