#include <conio.h>
#include <iostream>
using namespace std;

#include <ctime>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <fstream>

#include "Console.h"
using namespace System;
#include "Player.h"
#include "globals.h"
#include "Ghost.h"
#include "Fruits.h"

// Reset the console's cursor to bottom of screen.
void ResetCursor()
{
	Console::SetCursorPosition(0, Console::WindowHeight() - 1);
}

// TODO Part 3: Check collision function

bool CheckCollision (char maze[MAZE_ROWS][MAZE_COLS], Player *play, Ghost *ghusts[]);
void GameOver();

int main()
{
	bool exit = false;

#pragma region Look Nice
	// Get the handle of the console window.
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set font size/properties so the maze fits.
	CONSOLE_FONT_INFOEX font;
	font.nFont = 0;
	font.dwFontSize.X = 10;
	font.dwFontSize.Y = 20;
	font.FontFamily = 48;
	font.FontWeight = 400;
	font.cbSize = sizeof(font);
	SetCurrentConsoleFontEx(consoleHandle, false, &font);

	// What are our current properties?
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(info);
	GetConsoleScreenBufferInfoEx(consoleHandle, &info);

	// Correctly colored critters.
	info.ColorTable[DarkYellow] = RGB(246, 130, 31);
	info.ColorTable[Cyan] = RGB(27, 177, 230);
	info.ColorTable[Red] = RGB(237, 27, 36);
	info.ColorTable[Magenta] = RGB(245, 153, 178);
	info.ColorTable[Yellow] = RGB(254, 242, 0);

	// Set proper dimensions with no scroll bars.
	COORD winSize = CreateCoord(MAZE_COLS, MAZE_ROWS + 2);
	info.dwSize.X = info.dwMaximumWindowSize.X = info.srWindow.Right = winSize.X;
	info.dwSize.Y = info.dwMaximumWindowSize.Y = info.srWindow.Bottom = winSize.Y;
	SetConsoleScreenBufferInfoEx(consoleHandle, &info);
	SetConsoleScreenBufferSize(consoleHandle, winSize);

	// How large are we and the entire screen?
	HWND hwnd = GetConsoleWindow();
	RECT rect;
	GetWindowRect(hwnd, &rect);
	int	w  = rect.right - rect.left,
		h  = rect.bottom - rect.top,
		sw = GetSystemMetrics(SM_CXSCREEN),
		sh = GetSystemMetrics(SM_CYSCREEN);

	// Center us.
	MoveWindow(hwnd, (sw - w) >> 1, (sh - h) >> 1, w, h, TRUE);

	SetConsoleTitle(L"Pac-Man"); // Unicode string!
#pragma endregion

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);
	srand(static_cast<unsigned int>(time(nullptr)));

	char neim[40];

	while (true) { // Player  name validation 
		cout<<"Enter your name: ";
		if (cin.get(neim, sizeof neim) && sizeof neim > 1 ){
			break;
		}
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	Console::Clear();

	char maze[MAZE_ROWS][MAZE_COLS] =
	{
		// 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47   48   49   50   51   52   53   54
		{ MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', MUD, },
		{ MUD, '0', ' ', MUD, ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', MUD, ' ', '0', MUD, },
		{ MUD, 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MUD, ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MUD, ' ', ' ', ' ', MUD, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', MUD, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', ' ', ' ', MBL, MLR, MLR, MLR, MBR, ' ', ' ', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MUD, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MGD, MGD, MGD, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MBR, ' ', ' ', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', ' ', ' ', MBL, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MTR, ' ', ' ', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', ' ', ' ', MTL, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MUD, ' ', ' ', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', ' ', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MUD, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MBR, ' ', ' ', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', ' ', ' ', MBL, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MBL, MLR, MLR, MLR, MTR, ' ', MUD, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MUD, ' ', MTL, MLR, MLR, MLR, MBR, ' ', 'o', MUD, },
		{ MUD, '0', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', '0', MUD, },
		{ MBL, MLR, MLR, MTR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MTL, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MTR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MTL, MLR, MLR, MBR, },
		{ MTL, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MBR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MBL, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MTR, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, },
	};



	// Draw the maze.
	for (int i = 0; i < MAZE_ROWS; i++)
	{
		for (int j = 0; j < MAZE_COLS; j++)
		{
			if (MPP == maze[i][j])
				Console::ForegroundColor(Green);
			else if (MDOT == maze[i][j] || MGD == maze[i][j])
				Console::ForegroundColor(White);
			else
				Console::ForegroundColor(Blue);
			cout << maze[i][j];
		}
	}

	COORD playerStart = CreateCoord(27, 23);
	Player *newPlay = new Player(maze, playerStart ,neim);

	COORD startPos[4] = { { 27, 11 }, { 23, 14 }, { 27, 14 }, { 31, 14 } };
	ConsoleColor startColor[4] = { Red, Cyan, Magenta, DarkYellow };

	Ghost *ghost []= { 
		new Ghost(startColor[0], startPos[0]),
		new Ghost(startColor[1], startPos[1]), 
		new Ghost(startColor[2], startPos[2]), 
		new Ghost(startColor[3], startPos[3]),
	};

	newPlay->DisplayHUD();
	ResetCursor();

	Fruits fruity;

	while ( newPlay->GetLives() >= 0 || !exit){ // TODO Part 1: Game loop
		// Inside game loop:

		char letter;
		while (true){
			letter = _getch();
			if (cin.good() && ('a' == letter || 's' == letter || 'd' == letter || 'w' == letter || 'e' == letter ))
				break;

			cin.clear();
		}
		ResetCursor();

		COORD temp; //To have the TEMP variable on the scope after the switch.

		switch (letter){
		case 'a':{
			temp = CreateCoord(-2, 0);
			break;
				 }
		case 's':{
			temp = CreateCoord(0, 1);
			break;
				 }
		case 'd':{
			temp = CreateCoord(2, 0);
			break;
				 }
		case 'w':{
			temp = CreateCoord(0, -1);
			break;
				 }
		}
		if ('e' == letter)
			break;

		bool die = false;
		newPlay->Move(maze, temp, &fruity);
		
		int aux = fruity.GetSleep();
		int aux2 = fruity.GetFrames();

		if (!fruity.GetVisible()){
			//if not visible
			aux = aux -1;
			fruity.SetSleep(aux);

			if (0 == aux){
				fruity.SetVisible(true);
				maze[fruity.GetCoord().Y][fruity.GetCoord().X] = FRUIT;
				fruity.SetFrames(rand() % 20 + 20);
				fruity.Draw(maze);			
			}
		}
		else{ // if fruit is drawn
			aux2 = aux2 - 1;
			fruity.SetFrames(aux2);
			if (0 == aux2)
				fruity.Timeout(maze);
		}

	die = CheckCollision(maze, newPlay, ghost);

	if (!die){

		for (size_t i=0; i< NUM_GHOSTS; i++)
			ghost[i]->Move(maze, (ghost), newPlay);

		die = CheckCollision(maze, newPlay, ghost); 
	}

	if (die){
		if (0 < newPlay->GetLives() ){
			newPlay->Reset(maze, playerStart);
			for (size_t i=0; i<NUM_GHOSTS; i++){
				ghost[i]->Reset(maze, startPos[i]);
			}
			for (size_t i=0; i<NUM_GHOSTS; i++){
				ghost[i]->Draw(false);
			}
		}
		else{
			newPlay->Reset(maze, playerStart);
			newPlay->DisplayHUD();
			GameOver();
			break;
		} 
	}

	newPlay->DisplayHUD();
	ResetCursor();
}


// After game loop:
for (size_t i = 0; i < NUM_GHOSTS; i++)
	delete ghost[i];
Console::ResetColor();
ResetCursor();
delete newPlay;
//delete fruity;
system("pause");
return 0;
}

bool CheckCollision (char maze[MAZE_ROWS][MAZE_COLS], Player *play, Ghost *ghusts[]){

	for (size_t i=0; i<NUM_GHOSTS; i++){
		if ( CoordsEqual( ghusts[i]->GetCoord(), play->GetCoord()) ){
			if( play->GetPowerPellet() ){
				ghusts[i]->Kill(maze);
				play->GhostKilled();
			}
			else{
				play->Kill();
				return true;
			}
		}
	}
	return false;
} 

void GameOver(){
	Console::ForegroundColor(Green);
	Console::SetCursorPosition(22, 13);
	cout<< MTL; 
	for( size_t i=0; i<9; i++)
		cout<< MLR;
	cout << MTR;
	Console::SetCursorPosition(22, 14);
	cout<< MUD << "Game Over" << MUD;
	Console::SetCursorPosition(22, 15);
	cout<< MBL;
	for( size_t i=0; i<9; i++)
		cout<< MLR;
	cout << MBR;
}