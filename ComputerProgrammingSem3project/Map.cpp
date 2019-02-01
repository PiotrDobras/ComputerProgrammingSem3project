#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <typeinfo>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Map.h"
#include "ConsoleGraphics.h"
#include "Character.h"

#define MAP_FILES 20

//PLAY SCREEN - 50x25

/*------------------
-- MAP GENERATION --
------------------*/

bool IsStructural(char ch) {
	std::string stgl = "#"; //stgl - STructural GLyphs
	if (stgl.find(ch) != std::string::npos)
		return true;
	else
		return false;
}

void Map::GenGenerate(Player* p, int floor) {
	GenInitialize();
	int rms = floor * 2 + 2; //rms - RooMS
	if (rms > 36)
		rms = 36;
	GenPlaceRooms(rms);
	GenFixBlockedDoorways();
	GenRender();
	GenPlacePlayer(p);
}

void Map::GenInitialize() {
	for (int x = 0; x < ROOMS_W * 11; x++) {
		for (int y = 0; y < ROOMS_H * 11; y++) {
			raw[x][y] = '#';
		}
	}
	for (int x = 0; x < ROOMS_W; x++) {
		for (int y = 0; y < ROOMS_H; y++) {
			rooms[x][y] = false;
		}
	}
}

void Map::GenPrintCorner() {
	for (int x = 0; x < 50; x++) {
		for (int y = 0; y < 25; y++) {
			DrawAt(x, y, raw[x][y], 14);
		}
	}
}

void Map::GenPlaceRooms(int how_many) {
	how_many--;
	rooms[4][4] = true;
	GenReadRandomRoom(4, 4);
	while (how_many != 0) {
		int rx = rand() % ROOMS_W;
		int ry = rand() % ROOMS_H;
		if (rooms[rx][ry] == false) {
			int neighbours = 0;
			if (rx > 0)
				neighbours += rooms[rx - 1][ry];
			if (rx < ROOMS_W-1)
				neighbours += rooms[rx + 1][ry];
			if (ry > 0)
				neighbours += rooms[rx][ry - 1];
			if (ry < ROOMS_H-1)
				neighbours += rooms[rx][ry + 1];
			if (neighbours > 0) {
				rooms[rx][ry] = true;
				GenReadRandomRoom(rx, ry);
				how_many--;
			}
		}
	}
}

void Map::GenReadRandomRoom(int room_x, int room_y) {
	int randomFileNumber = rand() % MAP_FILES;
	stringstream ss;
	ss << "rooms/";
	ss << randomFileNumber;
	ss << ".txt";
	string randomFileName = ss.str();
	ifstream fin;
	fin.open(randomFileName);
	for (int y = room_y * 11; y < room_y * 11 + 11; y++) {
		for (int x = room_x * 11; x < room_x * 11 + 11; x++) {
			raw[x][y] = fin.get();
		}
		fin.get();
	}
	fin.close();
}

void Map::GenFixBlockedDoorways() {
	bool no_change;
	do {
		no_change = false;
		for (int x = 0; x < ROOMS_W * 11; x++) {
			for (int y = 0; y < ROOMS_H * 11; y++) {
				if (IsStructural(raw[x][y]) == false) {
					int neighbours = 4;
					if (x > 0)
						neighbours -= !IsStructural(raw[x - 1][y]);
					if (x < ROOMS_W * 11 - 1)
						neighbours -= !IsStructural(raw[x + 1][y]);
					if (y > 0)
						neighbours -= !IsStructural(raw[x][y - 1]);
					if (y < ROOMS_H * 11 - 1)
						neighbours -= !IsStructural(raw[x][y + 1]);
					if (neighbours >= 3) {
						raw[x][y] = '#';
						no_change = true;
					}
				}
			}
		}
	} while (no_change == true);
}

void Map::GenRender() {
	for (int x = 0; x < ROOMS_W * 11; x++) {
		for (int y = 0; y < ROOMS_H * 11; y++) {
			switch (raw[x][y]) {
			case '#':
				field[x][y] = new Wall();
				break;
			case '.':
				field[x][y] = new Floor();
				break;
			case ' ':
				field[x][y] = new Pit();
				break;
			case '+':
				field[x][y] = new Door();
				break;
			case '-':
				field[x][y] = new Bars(true);
				break;
			case '|':
				field[x][y] = new Bars(false);
				break;
			case '*':
				field[x][y] = new MagicCrystal();
				break;
			case '~':
				field[x][y] = new Water();
				break;
			default:
				field[x][y] = new Environment(); //this will print red exclamation marks to indicate something's wrong
				break;
			}
		}
	}
}

void Map::GenPlacePlayer(Player* p) {
	bool complete = false;
	while(complete == false){
		int randX = rand() % (ROOMS_W * 11);
		int randY = rand() % (ROOMS_H * 11);
		if (field[randX][randY]->GetBlocksMovement() == false) {
			p->SetX(randX);
			p->SetY(randY);
			complete = true;
		}
	}
}

/*----------------------
-- GAMEPLAY FUNCTIONS --
----------------------*/

Environment* Map::GetField(int x, int y) {
	return field[x][y];
}

GameObject* Map::GetObject(int x, int y) {
	return objects[x][y];
}

/*---------------
-- MAP DRAWING --
---------------*/

void Map::DrawRaycast(int x, int y, float direction, int range) {
	float const sx = 25.5; //prefix s - screen
	float const sy = 12.5;
	float fx = static_cast<float>(x) + 0.5; //prefix f - float
	float fy = static_cast<float>(y) + 0.5;
	float dir_rad = (M_PI / 180.0)*static_cast<float>(direction);
	float xstep = cos(dir_rad);
	float ystep = sin(dir_rad);
	float dx = 0.0; //prefix d - distance
	float dy = 0.0;
	while (abs(dy) <= range && abs(dx) <= range) {
		int cx = static_cast<int>(fx); //prefix c - cast
		int cy = static_cast<int>(fy);
		int scx = static_cast<int>(sx + dx);
		int scy = static_cast<int>(sy + dy);
		field[cx][cy]->SetSeen();
		field[cx][cy]->DrawSelf(scx, scy);
		if (field[cx][cy]->GetBlocksVision() && !(cx == x && cy == y))
			break;
		fx += xstep;
		dx += xstep;
		fy += ystep;
		dy += ystep;
	}
}

void Map::DrawSingle(int map_x, int map_y, int screen_x, int screen_y, bool gray) {
	if (map_x >= 0 && map_x < (ROOMS_W * 11) && map_y >= 0 && map_y < (ROOMS_H * 11))
		if(gray)
			field[map_x][map_y]->DrawSelfGray(screen_x, screen_y);
		else
			field[map_x][map_y]->DrawSelf(screen_x, screen_y);
}

void Map::DrawMapSeen(int center_x, int center_y) {
	int start_x = center_x - 25;
	int start_y = center_y - 12;
	int end_x = center_x + 26;
	int end_y = center_y + 13;
	int screen_x = 0;
	int screen_y = 0;
	for (int x = start_x; x < end_x; x++) {
		for (int y = start_y; y < end_y; y++) {
			DrawSingle(x, y, screen_x, screen_y, true);
			screen_y++;
		}
		screen_y = 0;
		screen_x++;
	}
}

void Map::DrawMapVisible(int center_x, int center_y, int range) {
	//all around raycast
	for (int i = 0; i < 360; i += 5) {
		if(i!=330) //prevents a very specific float rounding error
			       //we do not lose much by omitting this particular angle
			DrawRaycast(center_x, center_y, i, 8);
	}
	//dense raycasting in cardinal directions
	for (float i = -10; i <= 10; i += 0.5) {
		DrawRaycast(center_x, center_y, i, 8);
	}
	for (float i = 80; i <= 100; i += 0.5) {
		DrawRaycast(center_x, center_y, i, 8);
	}
	for (float i = 170; i <= 190; i += 0.5) {
		DrawRaycast(center_x, center_y, i, 8);
	}
	for (float i = 260; i <= 280; i += 0.5) {
		DrawRaycast(center_x, center_y, i, 8);
	}
}