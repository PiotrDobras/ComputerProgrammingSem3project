#pragma once
#include "Info.h"
#include "Character.h"
#include "Environment.h"

#define ROOMS_W 8
#define ROOMS_H 8

class Player; //forward declaration
class Enemy;
class Environment;
class Info;

class Map {
private:
	Environment* field[ROOMS_W * 11][ROOMS_H * 11];
	Item* objects[ROOMS_W * 11][ROOMS_H * 11];
	Enemy* enemies[ROOMS_W * 11][ROOMS_H * 11];
	char raw[ROOMS_W * 11][ROOMS_H * 11];
	bool rooms[ROOMS_W][ROOMS_H];
	int playerStartX;
	int playerStartY;
public:
	//generation functions
	void GenGenerate(Info* I, Player* p, int floor); //ENTIRE GENERATION PROCESS IN ONE FUNCTION
	void GenInitialize(); //call before doing anything else
	void GenPlaceRooms(int how_many); //call to start generating rooms from files
	void GenReadRandomRoom(int room_x, int room_y);
	void GenFixBlockedDoorways();
	void GenFixMapBorder();
	void GenRender(); //call this after completing generation
	void GenPlacePlayer(Player* p); //call this after completing render
	void GenPlaceItems(int floor);
	void GenEnemies(Info* I, Player* p, int floor);
	void GenPrintCorner(); //for DEBUG purposes only

	//gameplay functions
	Environment* GetField(int x, int y);
	Item* GetObject(int x, int y);
	void SetObject(int x, int y, Item* i);
	Enemy* GetEnemy(int x, int y);
	void SetEnemy(int x, int y, Enemy* e);
	void PassTurn(Info* I);

	//draw functions
	void DrawRaycast(int x, int y, float direction, int range);
	void DrawSingle(int map_x, int map_y, int screen_x, int screen_y, bool gray);
	void DrawMapSeen(int center_x, int center_y);
	void DrawMapVisible(int center_x, int center_y, int range);
};