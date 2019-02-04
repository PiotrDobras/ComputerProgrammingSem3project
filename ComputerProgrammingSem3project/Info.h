#pragma once
#include <string>

class Player;
class Item;
class Map;

#include "GameObject.h"
#include "Character.h"
#include "Event.h"
#include "Item.h"

class Info {
private:
	Player* player;
	Item* inventory[10];
	int selected = 0;
	int floor = 1;
	int turns_passed = 0;
	EventLog* eventlog[6];
public:
	Info(Player* p);
	int GetFloor() { return floor; }
	void PushEvent(EventLog* e);
	void PassTurn();
	void PickUpItem(Map* MG);
	Item* GetSelectedInventorySlot();
	void SelectInventorySlot(int which);

	//draw functions
	void DrawGUI();
	void DrawSeparator();
	void DrawSeparator(int y);
	void DrawBar(std::string label, int value, int value_max, int y, int color);
};