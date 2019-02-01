#include "Character.h"
#include "Map.h"
#include "ConsoleGraphics.h"

Player::Player() {
	SetGlyph('@', 15, true);
	health = 20;
	maxHealth = 20;
}

bool Player::Move(Map* MG, int direction)
{
	//see if the tile is blocked by environment
	switch (direction){ 
	case 0:
		if (MG->GetField(x + 1, y)->GetBlocksMovement() == false) {
			SetX(x + 1);
			return true;
		}break;
	case 90:
		if (MG->GetField(x, y - 1)->GetBlocksMovement() == false){
			SetY(y - 1);
			return true;
		}break;
	case 180:
		if (MG->GetField(x - 1, y)->GetBlocksMovement() == false){
			SetX(x - 1);
			return true;
		}break;
	case 270:
		if (MG->GetField(x, y + 1)->GetBlocksMovement() == false) {
			SetY(y + 1);
			return true;
		}break;
	default:
		return false;
	}
	return false;
}

Enemy::Enemy() {
	SetGlyph('E', 12, false);
	health = 10;
}
