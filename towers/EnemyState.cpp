#include "EnemyState.h"
#include <iostream>
const std::string EnemyState::s_menuID = "MENU";
void EnemyState::update() {
	// nothing for now
}
void EnemyState::render() {
	// nothing for now
}
bool EnemyState::onEnter() {
	std::cout << "entering MenuState\n";
	return true;
}
bool EnemyState::onExit() {
	std::cout << "exiting MenuState\n";
	return true;
}