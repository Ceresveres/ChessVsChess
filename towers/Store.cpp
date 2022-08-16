#include "Store.h"
#include <iostream>

using namespace std;

void PieceCard::print() {
	int dx = index * PIECE_CARD_WIDTH;
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
	for (auto& var : pieces) {
		var->print();
	}
}