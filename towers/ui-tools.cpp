#include "ui-tools.h"
#include <stdio.h>
#include <iostream>

void SSetWindowSize(int cols, int lines) {
//	char cmd[30];
//	sprintf_s(cmd, "mode con cols=%d lines=%d", cols, lines);
//	system(cmd);
}
//
void HHideCursor()
{
//	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//	CONSOLE_CURSOR_INFO info;
//	info.dwSize = 100;
//	info.bVisible = FALSE;
//	SetConsoleCursorInfo(consoleHandle, &info);
}
//
void Goto_XY(const int x, const int y) {
//	COORD position;
//	position.X = x;
//	position.Y = y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
//
void PrintWithColor(const string& str, int colorID) {
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
//	cout << str;
}