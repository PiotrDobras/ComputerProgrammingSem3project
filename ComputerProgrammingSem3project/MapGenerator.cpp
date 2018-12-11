#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

#include "MapGenerator.h"
#include "Environment.h"

#include "ConsoleGraphics.h" //temporary
#include <conio.h>

#define NUMBER_OF_ROOMS 1

using namespace std;

void MapGen::ClearMap() {
	for (int i = 0; i < HH; i++) {
		for (int j = 0; j < WH; j++) {
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

void MapGen::PlaceRooms(int sizeX, int sizeY) {
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {

			int randomFileNumber = rand() % NUMBER_OF_ROOMS;
			string randomFileName = "rooms/";
			randomFileName.append(to_string(randomFileNumber));
			randomFileName.append(".txt");
			ifstream file(randomFileName);
			if (file.good()) {
				for (int k = 0; k < 11; k++) {
					for (int l = 0; l < 11; l++) {
						rawMap[j * 11 + l][i * 11 + k] = file.get();
						DrawAt(j * 11 + l, i * 11 + k, rawMap[j * 11 + l][i * 11 + k], 6);
						UpdateScreen();
					} //l end
					file.get();
				} //k end
			} else {
				cout << "Unable to load " << randomFileName << " file." << endl;
			}

			_getch();

		} //j end
	} //i end
}

void MapGen::RenderMap() {
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
	_getch();
}