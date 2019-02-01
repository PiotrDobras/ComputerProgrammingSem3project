#pragma once
#include "Map.h"
#include "GameObject.h"

class Map; //forward declaration

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
	int armor;
	int maxArmor;
	int classArmor;
public:
	int GetX() { return x; };
	int GetY() { return y; };
	int GetHealth() { return health; };
	int GetHealthMax() { return maxHealth; };
	int GetArmor() { return armor; };
	int GetArmorMax() { return maxArmor; };
	int GetArmorClass() { return classArmor; };
	void SetX(int nx) { x = nx; }
	void SetY(int ny) { y = ny; }
	GameObject* Move(Map* MG, int direction);
	Player();
	~Player() {};
};

class Enemy : public Character {
	int health;
public:
	Enemy();
	virtual ~Enemy() {};
};