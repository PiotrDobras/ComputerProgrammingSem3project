#pragma once

class GameObject {
private:
	char glyph;
	char glyph_color;
	bool seen;
public:
	GameObject() { SetGlyph('!', 12, true); };
	virtual ~GameObject() {};
	virtual void Inspect() {};
	void SetGlyph(char gl, int gl_color, bool start_seen);
	void DrawSelf(int cx, int cy);
};

