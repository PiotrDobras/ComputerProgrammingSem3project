#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <string>
#include <fstream>

#include "ConsoleGraphics.h"
#include "GameObject.h"
#include "Environment.h"
#include "Character.h"
#include "MapGenerator.h"

using namespace std;

int main() {
	srand(time(NULL));
	
	ClearMap();

	Player *player = new Player();
	player->SetX(3);
	player->SetY(3);

	InitializeScreen();

	//TODO: LOOP
	//DRAWING PHASE
	PlaceRoom();
	PlaceRoom();
	PlaceRoom();
	PlaceRoom();
	PlaceRoom();
	PlaceRoom();
	PlaceRoom();
	PlaceRoom();
	PlaceRoom();
	PlaceRoom();

	RenderMap();

	for (int i = 0; i < HH * 11; i++) {
		for (int j = 0; j < WH * 11; j++) {
			layout[j][i]->Inspect();
			layout[j][i]->DrawSelf(j, i);
		}
	}

	player->DrawSelf(3, 3);
	UpdateScreen();
	//INPUT PHASE

	//EVALUATION PHASE
	
	_getch();
	return 0;
}