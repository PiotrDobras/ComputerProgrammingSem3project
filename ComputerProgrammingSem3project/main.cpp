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

using namespace std;

int main() {
	srand(time(NULL));

	Map* map = new Map();

	Player *player = new Player();
	player->SetX(3);
	player->SetY(3);

	bool terminate = false;

	InitializeScreen();

	map->GenGenerate(player, 1);

	while (terminate == false) {
		//DRAWING PHASE

		ClearScreen();

		map->DrawMapSeen(player->GetX(), player->GetY());
		map->DrawMapVisible(player->GetX(), player->GetY(), 2);

		player->DrawSelf(25, 12);

		UpdateScreen();

		//INPUT PHASE

		bool pass_turn = false;
		switch (_getch()) {
		case 100: //D
			pass_turn = player->Move(map, 0);
			break;
		case 119: //W
			pass_turn = player->Move(map, 90);
			break;
		case 97: //A
			pass_turn = player->Move(map, 180);
			break;
		case 115: //S
			pass_turn = player->Move(map, 270);
			break;
		case 27: //ESC
			terminate = true;
			break;
		default:
			break;
		}

		//EVALUATION PHASE

		if (pass_turn) {
			//do something here when turn has passed
			//like enemies moving, health regenerating and all that
		}

	}//main loop end

	return 0;
}