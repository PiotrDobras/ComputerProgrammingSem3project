#include <iostream>
#include <conio.h>

#include "ConsoleGraphics.h"
#include "GameObject.h"
#include "Environment.h"
#include "Character.h"

int main() {

	Environment *layout[77][77];
	GameObject *objects[77][77];

	Player *player = new Player();
	player->SetX(3);
	player->SetY(3);

	InitializeScreen();

	//TODO: LOOP
	//DRAWING PHASE
	player->DrawSelf(3, 3);
	UpdateScreen();
	//INPUT PHASE

	//EVALUATION PHASE
	
	_getch();
	return 0;
}