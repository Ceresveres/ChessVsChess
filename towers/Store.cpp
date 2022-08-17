#include "Store.h"
#include "Board.h"
#include <iostream>

using namespace std;

void PieceCard::print() {
	int dx = (index-1) * PIECE_CARD_WIDTH;
	int dy = (GRID_HEIGHT + 1) * GRID_NUM_Y + 3;

	string str( "  " + to_string(index) + ". " + name + "  -  $" + to_string(cost));
	
	Goto_XY(dx, dy);
	PrintWithColor(str);
}

void Store::init() {
	Goto_XY(2, (GRID_HEIGHT + 1) * GRID_NUM_Y + 1);
	PrintWithColor("Store");
	Goto_XY(0, (GRID_HEIGHT + 1) * GRID_NUM_Y + 2);
	string str(WINDOW_WIDTH, '-');
	PrintWithColor(str);
	refreshMoney();
	
	for (auto& var : pieces) {
		var->print();
	}
}

bool Store::buy(int choice, int x, int y, Board &board) {
	if (money >= pieces[choice - 1]->cost) {
		if (board.setPiece(x, y, choice)) {
			money -= pieces[choice - 1]->cost;
			refreshMoney();
			return true;
		}
	}
	return false;
}

void Store::refreshMoney() {
	string str(20, ' ');
	Goto_XY(WINDOW_WIDTH - 10, (GRID_HEIGHT + 1) * GRID_NUM_Y + 1);
	PrintWithColor(str);
	
	Goto_XY(WINDOW_WIDTH - 10, (GRID_HEIGHT + 1) * GRID_NUM_Y + 1);
	PrintWithColor("Bank: $" + to_string(money));
}