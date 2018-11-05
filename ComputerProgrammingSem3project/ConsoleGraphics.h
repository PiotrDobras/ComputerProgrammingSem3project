#pragma once

static char screen[80][25];
static char screen_next[80][25];
static int screen_color[80][25];
static int screen_color_next[80][25];

void InitializeScreen();
void UpdateScreen();
void DrawAt(int x, int y, char ch, int color);