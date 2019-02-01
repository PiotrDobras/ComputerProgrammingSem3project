#include "ConsoleGraphics.h"

#include "Info.h"

Info::Info(Player* p)
{
	player = p;
}

void Info::PushEvent(EventLog * e)
{
	delete eventlog[4];
	eventlog[4] = eventlog[3];
	eventlog[3] = eventlog[2];
	eventlog[2] = eventlog[1];
	eventlog[1] = eventlog[0];
	eventlog[0] = e;
}

void Info::PassTurn()
{
	for (int i = 0; i < 5; i++) {
		if (eventlog[i] != NULL) {
			eventlog[i]->PassTurn();
		}
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
		DrawAt(56, 5 + i, "Empty Slot", 7 + 8*(selected == i)); //TODO: DISPLAY ITEM NAME
	}

	DrawSeparator(15);

	DrawAt(52, 16, "FLOOR: " + std::to_string(GetFloor()), 15);
	DrawAt(52, 17, "TURN: [todo]", 15);
	DrawAt(52, 18, "KILL COUNT: [todo]", 15);

	DrawSeparator(19);

	for (int i = 0; i < 5; i++) {
		if(eventlog[i] != NULL)
			eventlog[i]->DrawEvent(20 + i);
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
