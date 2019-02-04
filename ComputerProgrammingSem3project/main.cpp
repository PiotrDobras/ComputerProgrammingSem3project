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

	map->GenGenerate(info, player, info->GetFloor());

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
		int gch = _getch();
		int inventory_number = 0;
		switch (gch) {
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
		case 103: //g
			info->PickUpItem(map);
			break;
		case 48: //numbers 0 through 10
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
			inventory_number = gch - 49;
			if (gch == 48)
				inventory_number = 9;
			info->SelectInventorySlot(inventory_number);
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
		map->PassTurn(info);

	}//main loop end

	return 0;
}