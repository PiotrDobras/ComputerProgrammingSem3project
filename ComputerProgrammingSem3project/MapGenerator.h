#pragma once
#include "GameObject.h"
#include "Environment.h"

#define WH 9
#define HH 9

class MapGen {
public:
	static char rawMap[WH * 11][HH * 11];
	static Environment *layout[WH * 11][HH * 11];
	static GameObject *objects[WH * 11][HH * 11];

	void ClearMap();
	void PlaceRooms(int sizeX, int sizeY);
	void RenderMap();
};