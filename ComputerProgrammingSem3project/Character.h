#pragma once
#include "GameObject.h"

class Character : public GameObject{
public:
	Character() {};
	virtual ~Character() {};
};

class Player : public Character {
	int health;
	int maxHealth;
	int experience;
	int level;
	int x;
	int y;
public:
	Player();
	~Player() {};
};

class Enemy : public Enemy {
	int health;
public:
	Enemy();
	virtual ~Enemy() {};
};