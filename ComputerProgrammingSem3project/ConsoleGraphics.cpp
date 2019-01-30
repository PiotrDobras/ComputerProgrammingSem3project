#include "ConsoleGraphics.h"
#include <iostream>
#include <Windows.h>

void InitializeScreen() {
	for (int i=0; i < 25; i++) {
		for (int j=0; j < 80; j++) {
			screen[j][i] = ' ';
			screen_next[j][i] = ' ';
			screen_color[j][i] = 15;
			screen_color_next[j][i] = 15;
		}
	}
	UpdateScreen();
}

void UpdateScreen() {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)0, (SHORT)0 };
	for (int i=0; i < 25; i++) {
		for (int j=0; j < 80; j++) {
			if (screen_color[j][i] != screen_color_next[j][i] || screen[j][i] != screen_next[j][i]) {
				coord = { (SHORT)j, (SHORT)i };
				SetConsoleCursorPosition(hOut, coord);
				SetConsoleTextAttribute(hOut, screen_color_next[j][i]);
				std::cout << screen_next[j][i];
				screen_color[j][i] = screen_color_next[j][i];
				screen[j][i] = screen_next[j][i];
			}
		}
	}
	coord = { (SHORT)0, (SHORT)0 };
	SetConsoleCursorPosition(hOut, coord);
	coord = { (SHORT)79, (SHORT)24 };
	SetConsoleCursorPosition(hOut, coord);
	SetConsoleTextAttribute(hOut, 7);
	std::cout.flush();
}

void DrawAt(int x, int y, char ch, int color) {
	if (x >= 0 && x < 80 && y >= 0 && y < 25) {
		screen_next[x][y] = ch;
		screen_color_next[x][y] = color;
	}
}

void ClearScreen() {
	for (int x = 0; x < 80; x++) {
		for (int y = 0; y < 25; y++) {
			screen_next[x][y] = ' ';
		}
	}
}