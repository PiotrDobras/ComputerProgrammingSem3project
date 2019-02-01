#pragma once
#include <string>

class EventLog {
private:
	std::string text;
	int timeout = 10;
	int color = 7;
public:
	EventLog(std::string event_message, int c);
	void DrawEvent(int y);
	void PassTurn();
	std::string GetText() { return text; }
};