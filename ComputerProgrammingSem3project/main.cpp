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

	MapGenerator* Map = new MapGenerator();

	Player *player = new Player();
	player->SetX(3);
	player->SetY(3);

	InitializeScreen();

	//TODO: LOOP
	//DRAWING PHASE

	Map->GenGenerate(player, 100);
	Map->DrawMapSeen(player->GetX(), player->GetY());

	player->DrawSelf(25, 12);

	UpdateScreen();
	//INPUT PHASE

	//EVALUATION PHASE
	
	_getch();
	return 0;
}