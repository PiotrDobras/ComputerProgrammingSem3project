#include "Character.h"
#include "Map.h"
#include "ConsoleGraphics.h"

Player::Player() {
	SetGlyph('@', 15, true);
	health = 20;
	maxHealth = 20;
	armor = 10;
	maxArmor = 10;
	classArmor = 1;
}

GameObject* Player::Move(Map* MG, int direction)
{

	Environment* f_obj = NULL;
	//see if the tile is blocked by environment
	switch (direction){ 
	case 0:
		if (MG->GetField(x + 1, y)->GetBlocksMovement() == false) {
			SetX(x + 1);
		}
		else {
			f_obj = MG->GetField(x + 1, y);
		}
		break;
	case 90:
		if (MG->GetField(x, y - 1)->GetBlocksMovement() == false){
			SetY(y - 1);
		}
		else {
			f_obj = MG->GetField(x, y - 1);
		}
		break;
	case 180:
		if (MG->GetField(x - 1, y)->GetBlocksMovement() == false){
			SetX(x - 1);
		}
		else {
			f_obj = MG->GetField(x - 1, y);
		}
		break;
	case 270:
		if (MG->GetField(x, y + 1)->GetBlocksMovement() == false) {
			SetY(y + 1);
		}
		else {
			f_obj = MG->GetField(x, y + 1);
		}
		break;
	}
	if (f_obj != NULL)
		return f_obj;

	return NULL;
}

Enemy::Enemy() {
	SetGlyph('E', 12, false);
	health = 10;
}
