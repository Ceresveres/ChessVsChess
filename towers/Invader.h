#pragma once
#include "ui-tools.h"
#include <string>

using namespace std;

class Game;
class Board;
class Invader {
protected:
	string name;
	int x, y;
	int counter = 0;

public:
	void setXY(int ix, int iy) { x = ix; y = iy; }

	friend class Game;
	friend class Grid;
};