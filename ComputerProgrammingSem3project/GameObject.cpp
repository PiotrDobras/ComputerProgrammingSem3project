#include "GameObject.h"
#include "ConsoleGraphics.h"

void GameObject::DrawSelf(int cx, int cy) {
	if (seen == true && cx >= 0 && cx < 80 && cy >= 0 && cy < 25) {
		DrawAt(cx, cy, glyph, glyph_color);
	}
}

void GameObject::SetGlyph(char gl, int gl_color, bool start_seen) {
	glyph = gl;
	glyph_color = gl_color;
	seen = start_seen;
} 