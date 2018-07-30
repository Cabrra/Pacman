#include "Console.h"
using namespace System;
#include <iostream>
using namespace std;
#include "globals.h"
#include "Player.h"
#include "Fruits.h"

//Overloaded constructor
Player::Player (char maze[MAZE_ROWS][MAZE_COLS], COORD const pos, char const *nme){ 
	
	this->position = CreateCoord(pos.X, pos.Y);
	maze[pos.Y][pos.X] = PAC;
	this->name = nullptr;
	SetName(nme);	
	this->score = 0;
	this->lives = 3;
	this->powerPellet = false;
	this->franes = 0;
	this->Draw(maze);
}

//Destructor
Player::~Player(){

	delete[] name;

}

//Move
void Player::Move (char maze[MAZE_ROWS][MAZE_COLS], COORD const posi, Fruits *fruit){
	if (this->powerPellet){
		this->franes -= 1;
		if ( 0 == this->franes)
			this->powerPellet = false;
	}
	COORD newCoord = CreateCoord(this->position.X + posi.X, this->position.Y + posi.Y);
	if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR  && maze[newCoord.Y][newCoord.X]  != MGD){	
		if (maze[newCoord.Y][newCoord.X] == MDOT) 
			this->score = this->score + 10;
		else if (maze[newCoord.Y][newCoord.X] == MPP){
			this->score += 50;
			this->powerPellet = true;
			this->franes = 25;
		}
		else if (maze[newCoord.Y][newCoord.X] == FRUIT){
			this->score +=  fruit->GetScore();
			fruit->Eaten(maze ); 
		}
		ClearSpot (maze);
		//UPDATE POSITION
		COORD warpCoordL = CreateCoord(WARP_LEFT_X, WARP_Y);
		COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
		if (CoordsEqual( newCoord, warpCoordL) && posi.X == -2){
			this->position.X = 53;
			this->position.Y = newCoord.Y;
		}
		else if (CoordsEqual( newCoord, warpCoordR) && posi.X == 2){
			this->position.X = 1;
			this->position.Y = newCoord.Y;
		}
		else 
			SetCoord (newCoord);
		Draw(maze);
	}
}

//Draw
void Player::Draw (char maze[MAZE_ROWS][MAZE_COLS]) const {

	maze[this->position.Y][this->position.X] = PAC;
	Console::SetCursorPosition((int)this->position.X, (int)this->position.Y);
	Console::ForegroundColor(Yellow);
	cout<<PAC;
	Console::ResetColor();
}

//ClearSpot
void Player::ClearSpot (char maze[MAZE_ROWS][MAZE_COLS]) const {
	maze[this->position.Y][this->position.X] = ' ';
	Console::SetCursorPosition((int)this->position.X, (int)this->position.Y);
	cout<<' ';
}

//HUD
void const Player::DisplayHUD() const{
	Console::SetCursorPosition(0, 31);
	cout<< "Name: " << this->name << '\t'<<"Score: "<<this->score<< '\t'<< "Lives: "<< this->lives;
}

//Reset

void Player::Reset(char maze[MAZE_ROWS][MAZE_COLS],  COORD const pos){
		ClearSpot(maze);
		this->SetCoord(pos);
		Draw(maze);
}

//SETERS
void Player::SetCoord (const COORD pos){
	this->position.X = pos.X;
	this->position.Y = pos.Y;
}

void Player::SetName (const char * const n){
	if (!n)
		return;

	delete[] name;

	int bytes = strlen(n) + 1;
	name = new char[bytes];
	strcpy_s(name, bytes, n);
}

void Player::SetScore (int sco){
	this->score = sco;
}

void Player::SetLives (int liv){
	this->lives = liv;
}
