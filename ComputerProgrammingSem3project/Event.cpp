#include "Event.h"
#include "ConsoleGraphics.h"

EventLog::EventLog(std::string event_message, int c)
{
	text = event_message;
	color = c;
}

void EventLog::DrawEvent(int y)
{
	DrawAt(52, y, text, color);
}

void EventLog::PassTurn()
{
	timeout--;
	if (timeout == 0)
		color = 8;
	if (timeout == -10)
		text = "";
}
