#include <iostream>

#include "ConsoleGraphics.h"
#include "GameObject.h"
#include "Environment.h"
#include "Character.h"

int main() {

	Environment *layout[77][77];
	GameObject *objects[77][77];

	Player *player = new Player();

	InitializeScreen();

	//TODO: LOOP
	//DRAWING PHASE

	//INPUT PHASE

	//EVALUATION PHASE

	system("pause");
	return 0;
}