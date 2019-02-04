#include "ConsoleGraphics.h"

#include "Info.h"

Info::Info(Player* p)
{
	player = p;
}

bool Info::IsNextLevel()
{
	if (next_level) {
		next_level = false;
		return true;
	}
	else {
		return false;
	}
}

void Info::PushEvent(EventLog * e)
{
	if (e == NULL)
		return;

	delete eventlog[5];
	eventlog[5] = eventlog[4];
	eventlog[4] = eventlog[3];
	eventlog[3] = eventlog[2];
	eventlog[2] = eventlog[1];
	eventlog[1] = eventlog[0];
	eventlog[0] = e;

	if (e->GetText() == "It fully healed you!") {
		player->ChangeHealth(999999, true);
	}
	if (e->GetText() == "You drink the Health Potion") {
		player->ChangeHealth(player->GetHealthMax()*0.6, true);
	}
	if (e->GetText() == "You reinforce your armor") {
		player->ImproveArmor();
	}
	if (e->GetText() == "You go down the stairs") {
		next_level = true;
		floor++;
	}
}

void Info::PassTurn()
{
	turns_passed++;

	for (int i = 0; i < 6; i++) {
		if (eventlog[i] != NULL) {
			eventlog[i]->PassTurn();
		}
	}

	for (int i = 0; i < 10; i++) {
		if (inventory[i] != NULL && inventory[i]->GetDurability() <= 0) {
			delete inventory[i];
			inventory[i] = NULL;
		}
	}
}

void Info::PickUpItem(Map* MG) {
	int x = player->GetX();
	int y = player->GetY();
	Item* temp;
	if (MG->GetObject(x, y) != NULL)
		PushEvent(new EventLog("Picked up " + MG->GetObject(x, y)->GetName(), 14));
	if (inventory[selected] != NULL)
		PushEvent(new EventLog("Dropped " + inventory[selected]->GetName(), 14));

	temp = MG->GetObject(x, y);
	MG->SetObject(x, y, inventory[selected]);
	inventory[selected] = temp;
}

Item * Info::GetSelectedInventorySlot()
{
	return inventory[selected];
}

void Info::SelectInventorySlot(int which)
{
	if (selected == which && inventory[selected] != NULL) {
		PushEvent(inventory[selected]->Use());
	}
	else {
		selected = which;
	}
}

void Info::DrawGUI()
{
	DrawSeparator();

	DrawBar("Health", player->GetHealth(), player->GetHealthMax(), 0, 12);
	DrawAt(59, 1, "[" + std::to_string(player->GetHealth()) + "/" + std::to_string(player->GetHealthMax()) + "]", 12);
	DrawBar("Armor", player->GetArmor(), player->GetArmorMax(), 2, 11);
	DrawAt(59, 3, "[" + std::to_string(player->GetArmor()) + "/" + std::to_string(player->GetArmorMax()) + "]:" + std::to_string(player->GetArmorClass()), 11);
	
	DrawSeparator(4);

	for (int i = 0; i < 10; i++) {
		DrawAt(52, 5 + i, std::to_string((i+1)%10) + ":", 7 + 8*(selected == i));
		DrawAt(56, 5 + i, inventory[i]->GetFullName(), 7 + 8*(selected == i));
	}

	DrawSeparator(15);

	DrawAt(52, 16, "FLOOR: " + std::to_string(GetFloor()), 15);
	DrawAt(52, 17, "TURN: " + std::to_string(turns_passed), 15);

	DrawSeparator(18);

	for (int i = 0; i < 6; i++) {
		if(eventlog[i] != NULL)
			eventlog[i]->DrawEvent(19 + i);
	}
}

void Info::DrawSeparator()
{
	for (int y = 0; y < 25; y++) {
		DrawAt(50, y, '|', 15);
	}
}

void Info::DrawSeparator(int y)
{
	for (int x = 52; x < 79; x++) {
		DrawAt(x, y, '-', 15);
	}
}

void Info::DrawBar(std::string label, int value, int value_max, int y, int color)
{
	if (label.length() > 7)
		DrawAt(52, y, "!!!!!!!", 12);
	else
		DrawAt(52, y, label, 15);

	float bars = (static_cast<float>(value) / static_cast<float>(value_max))*40.0;
	
	int posX = 59;
	while (posX < 79) {
		DrawAt(posX++, y, '.', 8);
	}
	posX = 59;
	while (bars > 0 && posX < 79) {
		DrawAt(posX++, y, ':', color-8);
		bars--;
	}
	posX = 59;
	while (bars > 0) {
		DrawAt(posX++, y, ';', color);
		bars--;
	}
}
