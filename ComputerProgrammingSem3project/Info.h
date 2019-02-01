#pragma once
#include <string>

#include "Character.h"
#include "Event.h"

class Info {
private:
	Player* player;
	GameObject* inventory[10];
	int selected = 0;
	int floor = 10;
	EventLog* eventlog[5];
public:
	Info(Player* p);
	int GetFloor() { return floor; }
	void PushEvent(EventLog* e);
	void PassTurn();

	//draw functions
	void DrawGUI();
	void DrawSeparator();
	void DrawSeparator(int y);
	void DrawBar(std::string label, int value, int value_max, int y, int color);
};