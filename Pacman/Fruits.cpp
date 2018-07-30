#include "Console.h"
using namespace System;
#include <iostream>
using namespace std;
#include "globals.h"
#include "Fruits.h"


Fruits::Fruits(){

	this->score = (rand()%10 + 1) * 25;
	this-> color = DarkRed;
	this-> ChangeSpot();
	this->sleep = rand() % 20 + 20;
	this-> frames = 0;
	this-> visible = false;

}

void Fruits::Draw(char maze[MAZE_ROWS][MAZE_COLS])  {

	Console::SetCursorPosition (this->position.X, this->position.Y);
	Console::ForegroundColor(this->color);
	cout << FRUIT;
	Console::ResetColor();
}

void Fruits::ChangeSpot(void){
	int num = rand() % 3 +1; // set spot
	 if (num == 1){
		COORD newPos = CreateCoord(27, 17);
		this->position.X = newPos.X;
		this->position.Y = newPos.Y;
	}
	else if (num == 2){
		COORD newPos = CreateCoord(17, 14);
		this->position.X = newPos.X;
		this->position.Y = newPos.Y;
	}
	else if (num == 3){
		COORD newPos = CreateCoord(37, 14);
		this->position.X = newPos.X;
		this->position.Y = newPos.Y;
	}
}

void Fruits::Eaten(char maze[MAZE_ROWS][MAZE_COLS]){ // eaten or timeout
	if (maze[this->GetCoord().Y][this->GetCoord().X] != PAC )
		maze[this->GetCoord().Y][this->GetCoord().X] = ' ';
	this-> visible = false;
	this-> SetSleep(rand() % 10 + 10);
	this->SetFrames(0);
}

void Fruits::Timeout (char maze[MAZE_ROWS][MAZE_COLS]){
	Console::SetCursorPosition((int)this->position.X, (int)this->position.Y);
	cout<< ' ';
	maze[this->position.Y][(int)this->position.X] = ' ';
	this->	SetSleep(rand() % 10 + 10);
	this->SetFrames(0);
	this->ChangeSpot();
}

void Fruits::ClearSpot (char maze[MAZE_ROWS][MAZE_COLS]) {
	Console::SetCursorPosition((int)this->position.X, (int)this->position.Y);
	cout<< ' ';
	maze[this->position.Y][(int)this->position.X] = ' ';
	}

void Fruits::SetCoord (const COORD pos){
	this->position = CreateCoord(pos.X, pos.Y);
}
void Fruits::SetFrames (const int fram ){
	this->frames = fram;
}
void Fruits::SetSleep (const int slep ){
	this->sleep = slep;
}

void Fruits::SetVisible( const bool visi){
	this->visible = visi;
}
