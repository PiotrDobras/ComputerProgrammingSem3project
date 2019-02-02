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
#include "Map.h"
#include "Info.h"

using namespace std;

int main() {
	srand(time(NULL));

	Map* map = new Map();

	Player* player = new Player();

	Info* info = new Info(player);

	bool terminate = false;

	InitializeScreen();

	map->GenGenerate(player, info->GetFloor());

	while (terminate == false) {
		//DRAWING PHASE

		ClearScreen();

		map->DrawMapSeen(player->GetX(), player->GetY());
		map->DrawMapVisible(player->GetX(), player->GetY(), 8);

		player->DrawSelf(25, 12);

		info->DrawGUI();

		UpdateScreen();

		//INPUT PHASE

		GameObject* obj = NULL;
		switch (_getch()) {
		case 100: //D
			obj = player->Move(map, 0);
			break;
		case 119: //W
			obj = player->Move(map, 90);
			break;
		case 97: //A
			obj = player->Move(map, 180);
			break;
		case 115: //S
			obj = player->Move(map, 270);
			break;
		case 27: //ESC
			terminate = true;
			break;
		default:
			break;
		}

		if (obj != NULL) {
			info->PushEvent(obj->Inspect());
		}
		info->PassTurn();
		map->PassTurn(player);

	}//main loop end

	return 0;
}