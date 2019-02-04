#pragma once
#include "Map.h"
#include "Info.h"
#include "GameObject.h"

class Map; //forward declaration
class Info;

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
	int GetArmorClass() { if (armor > 0) return classArmor; else return 0; };
	void SetX(int nx) { x = nx; }
	void SetY(int ny) { y = ny; }
	void ChangeHealth(int amount, bool ignoreArmour);
	void DamageArmor(int amount);
	void ImproveArmor();
	GameObject* Move(Map* MG, int direction);
	Player();
	~Player() {};
};

class Enemy : public Character {
protected:
	std::string name;
	int health;
	int attack;
	bool moved = false;
	//prefix w - weakness
	bool wPiercing;
	bool wBashing;
	bool wSlashing;
	Player* p;
	Info* I;
public:
	//For enemies, GameObject's SetSeen() controlls wether they're aggored or not
	Enemy() {
		name = "Unknown Enemy [Error]";
		SetGlyph('!', 12, false);
		wPiercing = false;
		wBashing = false;
		wSlashing = false;
		p = NULL;
		I = NULL;
	}
	Enemy(Info* In, Player* pl){
		name = "Enemy";
		SetGlyph('E', 12, false);
		wPiercing = false;
		wBashing = false;
		wSlashing = false;
		p = pl;
		I = In;
	};
	virtual ~Enemy() {};
	bool GetMoved() { return moved; };
	void SetMoved(bool mv) { moved = mv; };
	virtual void SetHealth(int amnt) { health = amnt; };
	virtual void SetAttack(int amnt) { attack = amnt; };
	int GetAttack() { return attack; };
	int ChangeHealth(int amnt, bool wP, bool wB, bool wS);
	void PassTurn(int PosX, int PosY, Map* MG);
	EventLog* Inspect();
};

class Rat : public Enemy {
public:
	Rat(Info* In, Player* pl) {
		name = "Rat";
		SetGlyph('r', 4, false);
		p = pl;
		I = In;
	}
	void SetHealth(int amnt) { health = amnt*0.5; };
};

class Skeleton : public Enemy {
public:
	Skeleton(Info* In, Player* pl) {
		name = "Skeleton";
		SetGlyph('S', 15, false);
		wBashing = true;
		p = pl;
		I = In;
	}
};

class Slime : public Enemy {
public:
	Slime(Info* In, Player* pl) {
		name = "Slime";
		SetGlyph('s', 10, false);
		wSlashing = true;
		p = pl;
		I = In;
	}
};

class Armadillo : public Enemy {
public:
	Armadillo(Info* In, Player* pl) {
		name = "Armadillo";
		SetGlyph('a', 15, false);
		wPiercing = true;
		p = pl;
		I = In;
	}
};

class ArmoredOrk : public Enemy {
public:
	ArmoredOrk(Info* In, Player* pl) {
		name = "Armored Ork";
		SetGlyph('O', 4, false);
		wPiercing = true;
		wBashing = true;
		p = pl;
		I = In;
	}
	void SetHealth(int amnt) { health = amnt*1.5; };
	void SetAttack(int amnt) { attack = amnt*1.5; };
};

class Zombie : public Enemy {
public:
	Zombie(Info* In, Player* pl) {
		name = "Zombie";
		SetGlyph('Z', 10, false);
		wPiercing = true;
		wSlashing = true;
		p = pl;
		I = In;
	}
	void SetHealth(int amnt) { health = amnt*1.5; };
	void SetAttack(int amnt) { attack = amnt*1.5; };
};

class Snake : public Enemy {
public:
	Snake(Info* In, Player* pl) {
		name = "Giant Snake";
		SetGlyph('s', 2, false);
		wSlashing = true;
		wBashing = true;
		p = pl;
		I = In;
	}
	void SetHealth(int amnt) { health = amnt*1.5; };
	void SetAttack(int amnt) { attack = amnt*1.5; };
};