#include "Character.h"

Player::Player() {
	health = 20;
	maxHealth = 20;
	experience = 0;
	level = 1;
	x = 3;
	y = 3;
}

Enemy::Enemy() {
	health = 10;
}