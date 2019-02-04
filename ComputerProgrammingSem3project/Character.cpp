#include <string>

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
		if (amount > 0)
			amount = 0;
		health += amount;
	}
	if (health > maxHealth)
		health = maxHealth;
	if (health < 0)
		health = 0;
}

void Player::IncreaseLevel()
{
	maxHealth += 10;
	ChangeHealth(20, true);
}

void Player::DamageArmor(int amount)
{
	amount = abs(amount);
	if(amount > GetArmorClass())
		amount = GetArmorClass();
	armor -= amount;
	if (armor <= 0) {
		armor = 0;
	}
}

void Player::ImproveArmor()
{
	maxArmor += 10;
	maxArmor += rand() % 10;
	armor = maxArmor;
	classArmor = classArmor + 1;
}

GameObject* Player::Move(Map* MG, int direction)
{

	GameObject* f_obj = NULL;
	//see if the tile is blocked by environment
	switch (direction){ 
	case 0:
		if (MG->GetField(x + 1, y)->GetBlocksMovement() == false && MG->GetEnemy(x + 1, y) == NULL) {
			SetX(x + 1);
		}
		else {
			f_obj = MG->GetField(x + 1, y);
			if (MG->GetEnemy(x + 1, y) != NULL)
				f_obj = MG->GetEnemy(x + 1, y);
		}
		break;
	case 90:
		if (MG->GetField(x, y - 1)->GetBlocksMovement() == false && MG->GetEnemy(x, y - 1) == NULL){
			SetY(y - 1);
		}
		else {
			f_obj = MG->GetField(x, y - 1);
			if (MG->GetEnemy(x, y - 1) != NULL)
				f_obj = MG->GetEnemy(x, y - 1);
		}
		break;
	case 180:
		if (MG->GetField(x - 1, y)->GetBlocksMovement() == false && MG->GetEnemy(x - 1, y) == NULL){
			SetX(x - 1);
		}
		else {
			f_obj = MG->GetField(x - 1, y);
			if (MG->GetEnemy(x - 1, y) != NULL)
				f_obj = MG->GetEnemy(x - 1, y);
		}
		break;
	case 270:
		if (MG->GetField(x, y + 1)->GetBlocksMovement() == false && MG->GetEnemy(x, y + 1) == NULL) {
			SetY(y + 1);
		}
		else {
			f_obj = MG->GetField(x, y + 1);
			if (MG->GetEnemy(x, y + 1) != NULL)
				f_obj = MG->GetEnemy(x, y + 1);
		}
		break;
	}
	if (f_obj != NULL)
		return f_obj;

	return NULL;
}

int Enemy::ChangeHealth(int amnt, bool wP, bool wB, bool wS) {
	if (wPiercing && wP || wBashing && wB || wSlashing && wS)
		amnt = amnt * 2;
	health += amnt;
	return -amnt;
}

void Enemy::PassTurn(int PosX, int PosY, Map* MG) {
	if (this->GetMoved())
		return;
	if (!this->GetSeen())
		return;
	SetMoved(true);
	if (health <= 0) {
		MG->SetEnemy(PosX, PosY, NULL);
		delete this;
		return;
	}
	int px = p->GetX(); //prefix p - player
	int py = p->GetY();
	int tx = px - PosX; //prefix t - target
	int ty = py - PosY;
	int nx = 0; //prefix n - normalized
	int ny = 0;
	if (tx != 0)
		nx = abs(tx) / tx;
	if (ty != 0)
		ny = abs(ty) / ty;
	if ((px == nx + PosX && ny == 0) || (py == ny + PosY && nx == 0)) {
		p->ChangeHealth(-MG->GetEnemy(PosX, PosY)->GetAttack(), false);
		std::string msg = name + " dealt " + std::to_string(attack) + " damage";
		I->PushEvent(new EventLog(msg, 12));
		return;
	}
	if (nx != 0) {
		if (!MG->GetField(PosX + nx, PosY)->GetBlocksMovement() && MG->GetEnemy(PosX + nx, PosY) == NULL) {
			Enemy* temp = MG->GetEnemy(PosX + nx, PosY);
			MG->SetEnemy(PosX + nx, PosY, this);
			MG->SetEnemy(PosX, PosY, temp);
			return;
		}
	}
	if (!MG->GetField(PosX, PosY + ny)->GetBlocksMovement() && MG->GetEnemy(PosX, PosY + ny) == NULL) {
		Enemy* temp = MG->GetEnemy(PosX, PosY + ny);
		MG->SetEnemy(PosX, PosY + ny, this);
		MG->SetEnemy(PosX, PosY, temp);
		return;
	}
}

EventLog* Enemy::Inspect() {
	Item* selected = I->GetSelectedInventorySlot();
	int sPower, sPiercing, sBashing, sSlashing; //prefix s - selected
	if (selected != NULL) {
		sPower = selected->GetPower(); 
		sPiercing = selected->IsPiercing();
		sBashing = selected->IsBashing();
		sSlashing = selected->IsSlashing();
		selected->DecreaseDurability();
	}
	else {
		sPower = 3;
		sPiercing = false;
		sBashing = false;
		sSlashing = false;
	}
	int dealt = ChangeHealth(-sPower, sPiercing, sBashing, sSlashing);
	return new EventLog("Dealt " + std::to_string(dealt) + " damage to " + name, 4);
}