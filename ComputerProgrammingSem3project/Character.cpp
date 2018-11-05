#include "Character.h"
#include "ConsoleGraphics.h"

Player::Player() {
	SetGlyph('@', 15, true);
	health = 20;
	maxHealth = 20;
	experience = 0;
	level = 1;
}

Enemy::Enemy() {
	SetGlyph('E', 12, false);
	health = 10;
}
