#pragma once
#include <string>
#include "Event.h"

class GameObject {
private:
	char glyph;
	char glyph_color;
	bool seen;
public:
	GameObject() { SetGlyph('!', 12, true); };
	virtual ~GameObject() {};
	virtual EventLog* Inspect() { return new EventLog("ERROR: You weren't supposed to see this", 12); };
	void SetSeen() { seen = true; }
	bool GetSeen() { return seen; }
	void SetGlyph(char gl, int gl_color, bool start_seen);
	void DrawSelf(int cx, int cy);
	void DrawSelfGray(int cx, int cy);
};

