#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <typeinfo>

#include "MapGenerator.h"
#include "ConsoleGraphics.h"
#include "Character.h"

#define MAP_FILES 5

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

void MapGenerator::GenGenerate(Player* p, int floor) {
	GenInitialize();
	int rms = floor * 2 + 2; //rms - RooMS
	if (rms > 36)
		rms = 36;
	GenPlaceRooms(rms);
	GenFixBlockedDoorways();
	GenRender();
	GenPlacePlayer(p);
}

void MapGenerator::GenInitialize() {
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

void MapGenerator::GenPrintCorner() {
	for (int x = 0; x < 50; x++) {
		for (int y = 0; y < 25; y++) {
			DrawAt(x, y, raw[x][y], 14);
		}
	}
}

void MapGenerator::GenPlaceRooms(int how_many) {
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

void MapGenerator::GenReadRandomRoom(int room_x, int room_y) {
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

void MapGenerator::GenFixBlockedDoorways() {
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

void MapGenerator::GenRender() {
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
			default:
				field[x][y] = new Environment(); //this will print red exclamation marks to indicate something's wrong
				break;
			}
		}
	}
}

void MapGenerator::GenPlacePlayer(Player* p) {
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

/*---------------
-- MAP DRAWING --
---------------*/

void MapGenerator::DrawSingle(int map_x, int map_y, int screen_x, int screen_y) {
	if (map_x >= 0 && map_x < (ROOMS_W * 11) && map_y >= 0 && map_y < (ROOMS_H * 11))
		field[map_x][map_y]->DrawSelf(screen_x, screen_y);
}

void MapGenerator::DrawMapSeen(int center_x, int center_y) {
	int start_x = center_x - 25;
	int start_y = center_y - 12;
	int end_x = center_x + 26;
	int end_y = center_y + 13;
	int screen_x = 0;
	int screen_y = 0;
	for (int x = start_x; x < end_x; x++) {
		for (int y = start_y; y < end_y; y++) {
			DrawSingle(x, y, screen_x, screen_y);
			screen_y++;
		}
		screen_y = 0;
		screen_x++;
	}
}

void MapGenerator::DrawMapVisible() {

}