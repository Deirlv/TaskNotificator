#pragma once
#include<iostream>
#include <windows.h>

enum Color
{
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8,
	LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

namespace render
{

	void SetColor(int text, int background);

	void gotoxy(int x, int y);

	void renderFrame(unsigned int x, unsigned int y, const char x_symbol, const char down_x_symbol, const char y_symbol);

	void renderText(std::string text, unsigned int x, unsigned int y);

}
