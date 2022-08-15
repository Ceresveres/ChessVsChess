#pragma once
#include <Windows.h>
#include <string>

using namespace std;

const int GRID_NUM_Y = 5;
const int GRID_HEIGHT = 4;

const int GRID_NUM_X = 8;
const int GRID_WIDTH = 9;

const int WINDOW_WIDTH = GRID_NUM_X * (GRID_WIDTH + 1) + 1;
const int WINDOW_HEIGHT = GRID_NUM_Y * (GRID_HEIGHT + 1) + 20;

void SetWindowSize(int cols, int lines);
void HideCursor();
void Goto_XY(const int x, const int y);
void PrintWithColor(const string& str, int colorID=FOREGROUND_RED);

enum EnemyType {basic};