#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

#include "MapGenerator.h"
#include "Environment.h"

#define NUMBER_OF_ROOMS 1

using namespace std;

void ClearMap() {
	for (int i = 0; i < HH; i++) {
		for (int j = 0; j < WH; j++) {
			connections[j][i] = 0;
			for (int k = 0; k < 11; k++) {
				for (int l = 0; l < 11; l++) {
					rawMap[j * 11 + l][i * 11 + k] = '#';
					delete layout[j * 11 + l][i * 11 + k];
					delete objects[j * 11 + l][i * 11 + k];
				}
			}
		}
	}
}

void PlaceRoom() {
	int randomFileNumber = rand() % NUMBER_OF_ROOMS;
	string randomFileName = "rooms/";
	randomFileName.append(to_string(randomFileNumber));
	randomFileName.append(".txt");

	int roomX;
	int roomY;
	int neighbours;

	if (noRooms) {
		roomX = WH / 2;
		roomY = HH / 2;
	}
	else {
		do {
			neighbours = 0;
			roomX = 1 + rand() % (WH - 2);
			roomY = 1 + rand() % (HH - 2);
			neighbours += connections[roomX + 1][roomY];
			neighbours += connections[roomX - 1][roomY];
			neighbours += connections[roomX][roomY + 1];
			neighbours += connections[roomX][roomY - 1];
		} while (neighbours == 0);
	}

	connections[roomX][roomY] = 1;

	ifstream roomFile(randomFileName);
	if (roomFile.good()) {
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				rawMap[roomX * 11 + j][roomY * 11 + i] = roomFile.get();
			}
			roomFile.get();
		}
	} else {
		cout << "File Not Found: " << randomFileName;
	}
}

void RenderMap() {
	for (int i = 0; i < HH * 11; i++) {
		for (int j = 0; j < WH * 11; j++) {
			switch (rawMap[j][i]) {
			case '#':
				layout[j][i] = new Wall();
				break;
			case '.':
				layout[j][i] = new Floor();
				break;
			default:
				layout[j][i] = new Environment();
				break;
			}
		}
	}
}