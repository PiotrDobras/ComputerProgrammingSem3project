#pragma once
#include "GameObject.h"

class Environment : public GameObject {
protected:
	bool blocksMovement;
	bool blocksVision;
public:
	Environment() {};
	virtual ~Environment() {};
};

class Wall : public Environment {
public:
	Wall() {
		SetGlyph('#', 15, false);
		blocksMovement = true;
		blocksVision = true;
	};
	virtual ~Wall() {};
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
};

class Obstacle : public Environment {
public:
	Obstacle() {
		SetGlyph('%', 0, false);
		blocksMovement = true;
		blocksVision = false;
	};
	virtual ~Obstacle() {};
};