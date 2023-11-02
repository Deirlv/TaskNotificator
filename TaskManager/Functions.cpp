#include "Functions.h"
#include<iostream>

void render::SetColor(int text, int background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((background << 4) | text));
}

void render::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void render::renderFrame(const unsigned int x, const unsigned int y, const char x_symbol, const char down_x_symbol, const char y_symbol)
{
	for (size_t j = 0; j < x; j++)
	{
		render::gotoxy(0 + j, 0);
		std::cout << x_symbol;
	}
	for (size_t i = 0; i < y - 2; i++)
	{
		render::gotoxy(0, 1 + i);
		std::cout << y_symbol;
		render::gotoxy(x - 1, 1 + i);
		std::cout << y_symbol;
	}
	for (size_t j = 0; j < x; j++)
	{
		render::gotoxy(x + j, y - 3);
		std::cout << down_x_symbol;
	}


}

void render::renderText(std::string text, unsigned int x, unsigned int y)
{
	if (text == "Super Tests")
	{
		render::gotoxy(x, y++);
		std::cout << "   _____                         _______        _       ";
		render::gotoxy(x, y++);
		std::cout << "  / ____|                       |__   __|      | |      ";
		render::gotoxy(x, y++);
		std::cout << " | (___  _   _ _ __   ___ _ __     | | ___  ___| |_ ___ ";
		render::gotoxy(x, y++);
		std::cout << "  \\___ \\| | | | '_ \\ / _ \\ '__|    | |/ _ \\/ __| __/ __|";
		render::gotoxy(x, y++);
		std::cout << "  ____) | |_| | |_) |  __/ |       | |  __/\\__ \\ |_\\__ \\";
		render::gotoxy(x, y++);
		std::cout << " |_____/ \\__,_| .__/ \\___|_|       |_|\\___||___/\\__|___/";
		render::gotoxy(x, y++);
		std::cout << "              | |                                       ";
		render::gotoxy(x, y);
		std::cout << "              |_|                                       ";
	}

	if (text == "Admin")
	{
		render::gotoxy(x, y++);
		std::cout << "              _           _       ";
		render::gotoxy(x, y++);
		std::cout << "     /\\      | |         (_)      ";
		render::gotoxy(x, y++);
		std::cout << "    /  \\   __| |_ __ ___  _ _ __  ";
		render::gotoxy(x, y++);
		std::cout << "   / /\\ \\ / _` | '_ ` _ \\| | '_ \\ ";
		render::gotoxy(x, y++);
		std::cout << "  / ____ \\ (_| | | | | | | | | | |";
		render::gotoxy(x, y);
		std::cout << " /_/    \\_|\__,_|_| |_| |_|_|_| |_|";
	}
	if (text == "Student")
	{
		render::gotoxy(x, y++);
		std::cout << "   _____ _             _            _   ";
		render::gotoxy(x, y++);
		std::cout << "  / ____| |           | |          | |  ";
		render::gotoxy(x, y++);
		std::cout << " | (___ | |_ _   _  __| | ___ _ __ | |_ ";
		render::gotoxy(x, y++);
		std::cout << "  \\___ \\| __| | | |/ _` |/ _ \\ '_ \\| __|";
		render::gotoxy(x, y++);
		std::cout << "  ____) | |_| |_| | (_| |  __/ | | | |_ ";
		render::gotoxy(x, y);
		std::cout << " |_____/ \\__|\\__,_|\\__,_|\\___|_| |_|\\__|";
	}

}


