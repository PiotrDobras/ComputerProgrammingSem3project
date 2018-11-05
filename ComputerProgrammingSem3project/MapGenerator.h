#pragma once
#include "GameObject.h"
#include "Environment.h"

#define WH 7
#define HH 7
//actual map generated is smaller by 2 in each dimension

static char rawMap[WH*11][HH*11];
static Environment *layout[WH*11][HH*11];
static GameObject *objects[WH*11][HH*11];
static int connections[WH][HH];
static bool noRooms = true;

void ClearMap();
void PlaceRoom();
void RenderMap();