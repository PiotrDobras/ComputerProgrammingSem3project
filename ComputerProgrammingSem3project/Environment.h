#pragma once
#include <iostream>

#include "GameObject.h"

using namespace std;

class Environment : public GameObject {
protected:
	bool blocksMovement;
	bool blocksVision;
public:
	bool GetBlocksMovement() { return blocksMovement; }
	bool GetBlocksVision() { return blocksVision; }
	Environment() {};
	virtual ~Environment() {};
};

/*
  [ [ BASIC STRUCTURE ] ]
*/

class Wall : public Environment {
public:
	Wall() {
		SetGlyph('#', 15, false);
		blocksMovement = true;
		blocksVision = true;
	};
	virtual ~Wall() {};
	EventLog* Inspect() { return new EventLog("This is a wall", 7); }
};

class Floor : public Environment {
public:
	Floor() {
		SetGlyph('.', 7, false);
		blocksMovement = false;
		blocksVision = false;
	};
	virtual ~Floor() {};
};

class Pit : public Environment {
public:
	Pit() {
		SetGlyph(' ', 0, false);
		blocksMovement = true;
		blocksVision = false;
	};
	virtual ~Pit() {};
	EventLog* Inspect() { return new EventLog("This is a bottomless pit", 7); }
};

class Door : public Environment {
public:
	Door() {
		SetGlyph('+', 4, false);
		blocksMovement = true;
		blocksVision = true;
	};
	virtual ~Door() {};
	EventLog* Inspect() { 
		blocksMovement = false;
		blocksVision = false;
		SetGlyph('.', 4, true);
		return new EventLog("You open the door", 6);
	}
};

/*
  [ [ PRETTY EXTRAS ] ]
*/

class Bars : public Environment {
public:
	Bars(bool horizontal) {
		if (horizontal)
			SetGlyph('-', 15, false);
		else
			SetGlyph('|', 15, false);
		blocksMovement = true;
		blocksVision = false;
	};
	virtual ~Bars() {};
	EventLog* Inspect() { return new EventLog("These are prison bars", 7); }
};

class MagicCrystal : public Environment {
protected:
	bool active;
public:
	MagicCrystal() {
		SetGlyph('*', 13, true);
		blocksMovement = true;
		blocksVision = false;
		active = true;
	};
	virtual ~MagicCrystal() {};
	EventLog* Inspect() {
		SetGlyph('*', 5, true);
		if (active) {
			active = false;
			return new EventLog("It fully healed you!", 13);
		}
		else {
			return new EventLog("This is a magic crystal", 7);
		}
	}
};

class Water : public Environment {
public:
	Water() {
		SetGlyph('~', 11, false);
		blocksMovement = true;
		blocksVision = false;
	};
	virtual ~Water() {};
	EventLog* Inspect() { return new EventLog("This is deep water", 7); }
};