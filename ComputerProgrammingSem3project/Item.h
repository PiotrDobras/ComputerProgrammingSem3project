#pragma once
#include "GameObject.h"

class Item : public GameObject {
protected:
	std::string name;
	int power;
	int durability;
	bool consumable;
	bool dPiercing; // prefix d - damage
	bool dBashing;
	bool dSlashing;
	bool advanced;
public:
	Item() {
		name = "Unknown Item [Error]";
		power = 3; //3 is bare fist damage
		durability = 1;
		consumable = false;
		dPiercing = false;
		dBashing = false;
		dSlashing = false;
		advanced = false;
	}
	virtual ~Item() {};
	std::string GetName() { return name; }
	std::string GetFullName();
	int GetPower() { return power; };
	int GetDurability() { return durability; };
	virtual void SetStats(int floor);
	bool IsConsumable() { return consumable; };
	bool IsPiercing() { return dPiercing; };
	bool IsBashing() { return dBashing; };
	bool IsSlashing() { return dSlashing; };
	void DecreaseDurability() { durability -= 1; }
	virtual EventLog* Use() { return NULL; };
};

// BASIC WEAPONS //

class Sword : virtual public Item {
public:
	Sword() {
		SetGlyph(')', 11, false);
		name = "Sword";
		dSlashing = true;
	}
	virtual ~Sword() {};
};

class Mace : virtual public Item {
public:
	Mace() {
		SetGlyph('(', 4, false);
		name = "Mace";
		dBashing = true;
	}
	virtual ~Mace() {};
};

class Spear : virtual public Item {
public:
	Spear() {
		SetGlyph('/', 15, false);
		name = "Spear";
		dPiercing = true;
	}
	virtual ~Spear() {};
};

// ADVANCED WEAPONS //

class BattleAxe : public Sword, public Mace{
public:
	BattleAxe() {
		SetGlyph('%', 15, false);
		name = "Battle Axe";
		advanced = true;
	}
	~BattleAxe() {};
};

class MorningStar : public Mace, public Spear {
public:
	MorningStar() {
		SetGlyph('!', 14, false);
		name = "Morning Star";
		advanced = true;
	}
	~MorningStar() {};
};

class HalberedFlag : public Sword, public Spear {
public:
	HalberedFlag() {
		SetGlyph('|', 10, false);
		name = "Halbered Flag";
		advanced = true;
	}
	~HalberedFlag() {};
};

// CONSUMABLES //

class HealthPotion : public Item {
public:
	HealthPotion() {
		SetGlyph('^', 12, false);
		name = "Health Potion";
		consumable = true;
	}
	EventLog* Use() { DecreaseDurability(); return new EventLog("You drink the Health Potion", 10); };
};

class ArmorKit : public Item {
public:
	ArmorKit() {
		SetGlyph('^', 13, false);
		name = "Armor Kit";
		consumable = true;
	}
	EventLog* Use() { DecreaseDurability(); return new EventLog("You reinforce your armor", 10); };
};