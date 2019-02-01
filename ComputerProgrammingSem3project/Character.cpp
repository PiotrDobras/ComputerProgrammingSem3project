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

void Player::ChangeHealth(int amount, bool ignoreArmour)
{
	if (amount > 0) {
		health += amount;
	}
	else {
		if (!ignoreArmour) {
			DamageArmor(amount);
			amount += GetArmorClass();
		}
		if (amount < 0)
			amount = 0;
		health += amount;
	}
	if (health > maxHealth)
		health = maxHealth;
	if (health < 0)
		health = 0;
}

void Player::DamageArmor(int amount)
{
	amount = abs(amount);
	if(amount > GetArmorClass())
		amount = GetArmorClass();
	armor -= amount;
	if (armor <= 0) {
		armor = 0;
		maxArmor = 1;
		classArmor = 0;
	}
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
