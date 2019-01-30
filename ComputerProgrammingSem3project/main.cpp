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