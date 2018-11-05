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
		blocksMovement = true;
		blocksVision = true;
	};
	virtual ~Wall() {};
};

class Floor : public Environment {
public:
	Floor() {
		blocksMovement = false;
		blocksVision = false;
	};
	virtual ~Floor() {};
};

class Pit : public Environment {
public:
	Pit() {
		blocksMovement = true;
		blocksVision = false;
	};
	virtual ~Pit() {};
};

class Obstacle : public Environment {
public:
	Obstacle() {
		blocksMovement = true;
		blocksVision = false;
	};
	virtual ~Obstacle() {};
};