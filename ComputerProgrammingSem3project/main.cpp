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

	//OUTSIDE GAME LOOP
	while (true) {

		Map* map = new Map();

		Player* player = new Player();

		Info* info = new Info(player);

		bool terminate = false;

		InitializeScreen();

		map->GenGenerate(info, player, info->GetFloor());

		//--== DRAW MAIN MENU ==--//
		ClearScreen();

		int pX = 4; //prefix p - padding
		int pY = 3;
		int Y = 0;

		DrawAt(pX, pY + Y++, "    ______              ", 3);
		DrawAt(pX, pY + Y++, "   (, /   )          /) ", 3);
		DrawAt(pX, pY + Y++, "    _/___/ _  _/_ _ (/  ", 3);
		DrawAt(pX, pY + Y++, "    /     (_(_(__(__/ )_", 3);
		DrawAt(pX, pY + Y++, " ) /                    ", 3);
		DrawAt(pX, pY + Y++, "(_/                     ", 3);
		Y = 4;
		int X = 5;
		DrawAt(pX + X, pY + Y++, " ______            _        _______  _______  _______  _       ", 12);
		DrawAt(pX + X, pY + Y++, "(  __  \\ |\\     /|( (    /|(  ____ \\(  ____ \\(  ___  )( (    /|", 12);
		DrawAt(pX + X, pY + Y++, "| (  \\  )| )   ( ||  \\  ( || (    \\/| (    \\/| (   ) ||  \\  ( |", 4);
		DrawAt(pX + X, pY + Y++, "| |   ) || |   | ||   \\ | || |      | (__    | |   | ||   \\ | |", 4);
		DrawAt(pX + X, pY + Y++, "| |   | || |   | || (\\ \\) || | ____ |  __)   | |   | || (\\ \\) |", 4);
		DrawAt(pX + X, pY + Y++, "| |   ) || |   | || | \\   || | \\_  )| (      | |   | || | \\   |", 4);
		DrawAt(pX + X, pY + Y++, "| (__/  )| (___) || )  \\  || (___) || (____/\\| (___) || )  \\  |", 4);
		DrawAt(pX + X, pY + Y++, "(______/ (_______)|/    )_)(_______)(_______/(_______)|/    )_)", 12);

		DrawAt(24, 18, "= = Press ANY key to start = =", 15);
		DrawAt(28, 20, "- Press ESC to leave -", 8);

		UpdateScreen();
		if (_getch() == 27)
			return 0;

		//MAIN GAME LOOP
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

			//PROCESSING PHASE

			if (obj != NULL) {
				info->PushEvent(obj->Inspect());
			}
			info->PassTurn();
			map->PassTurn(info);

			if (player->GetHealth() == 0)
				break;

			if (info->IsNextLevel()) {
				map->GenGenerate(info, player, info->GetFloor());
				player->IncreaseLevel();
			}

		}//main loop end

		//game over screen
		ClearScreen();

		pX = 16; //prefix p - padding
		pY = 2;
		Y = 0;

		DrawAt(pX, pY + Y++, " ::::::::      :::     ::::    ::::  :::::::::: ", 12);
		DrawAt(pX, pY + Y++, ":+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:        ", 12);
		DrawAt(pX, pY + Y++, "+:+         +:+   +:+  +:+ +:+:+ +:+ +:+        ", 12);
		DrawAt(pX, pY + Y++, ":#:        +#++:++#++: +#+  +:+  +#+ +#++:++#   ", 12);
		DrawAt(pX, pY + Y++, "+#+   +#+# +#+     +#+ +#+       +#+ +#+        ", 12);
		DrawAt(pX, pY + Y++, "#+#    #+# #+#     #+# #+#       #+# #+#        ", 12);
		DrawAt(pX, pY + Y++, " ########  ###     ### ###       ### ########## ", 12);
		DrawAt(pX, pY + Y++, "                                                ", 12);
		DrawAt(pX, pY + Y++, " ::::::::   :::     :::  ::::::::::  :::::::::  ", 12);
		DrawAt(pX, pY + Y++, ":+:    :+:  :+:     :+:  :+:         :+:    :+: ", 12);
		DrawAt(pX, pY + Y++, "+:+    +:+  +:+     +:+  +:+         +:+    +:+ ", 12);
		DrawAt(pX, pY + Y++, "+#+    +:+  +#+     +:+  +#++:++#    +#++:++#:  ", 12);
		DrawAt(pX, pY + Y++, "+#+    +#+   +#+   +#+   +#+         +#+    +#+ ", 12);
		DrawAt(pX, pY + Y++, "#+#    #+#    #+#+#+#    #+#         #+#    #+# ", 12);
		DrawAt(pX, pY + Y++, " ########       ###      ##########  ###    ### ", 12);
		DrawAt(16, 19,       "          You survived until floor: " + std::to_string(info->GetFloor()), 15);
		DrawAt(16, 20,       "      It took you " + std::to_string(info->GetTurns()) + " turns to get there", 15);
		DrawAt(16, 22,       "        = Press ANY key to restart =", 8);

		UpdateScreen();
		_getch();

	}//outside game loop end

	return 0;
}