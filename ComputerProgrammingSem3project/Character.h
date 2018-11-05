#pragma once
#include "GameObject.h"

class Character : public GameObject{
public:
	Character() {};
	virtual ~Character() {};
};

class Player : public Character {
protected:
	int x;
	int y;
	int health;
	int maxHealth;
	int experience;
	int level;
public:
	int GetX() { return x; };
	int GetY() { return y; };
	void SetX(int nx) { x = nx; }
	void SetY(int ny) { y = ny; }
	Player();
	~Player() {};
};

class Enemy : public Character {
	int health;
public:
	Enemy();
	virtual ~Enemy() {};
};