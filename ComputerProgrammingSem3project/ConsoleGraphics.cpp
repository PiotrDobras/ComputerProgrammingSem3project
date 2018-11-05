#include "ConsoleGraphics.h"
#include <iostream>
#include <Windows.h>

void InitializeScreen() {
	for (int i=0; i < 25; i++) {
		for (int j=0; j < 80; j++) {
			screen[j][i] = '#';
			screen_next[j][i] = ' ';
			screen_color[j][i] = 4;
			screen_color_next[j][i] = 15;
		}
	}
	UpdateFrame();
}

void UpdateFrame() {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	for (int i=0; i < 25; i++) {
		for (int j=0; j < 80; j++) {
			if (screen_color[j][i] != screen_color_next[j][i] || screen[j][i] != screen_next[j][i]) {
				COORD coord = { (SHORT)j, (SHORT)i };
				SetConsoleCursorPosition(hOut, coord);
				SetConsoleTextAttribute(hOut, screen_color_next[j][i]);
				std::cout << screen_next[j][i];
				screen_color[j][i] = screen_color_next[j][i];
				screen[j][i] = screen_next[j][i];
			}
		}
	}
	std::cout.flush();
}

void DrawAt(int x, int y, char ch, int color) {
	screen_next[x][y] = ch;
	screen_color_next[x][y] = color;
}