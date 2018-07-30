#include "Console.h"
using namespace System;
#include <iostream>
using namespace std;
#include "globals.h"
#include "Ghost.h"

//Overloaded constructor

Ghost::Ghost(ConsoleColor colr, COORD posi){
	this->SetCoord(posi);
	this->color = colr;
	this->scared = White;
	this->avoidMove = -1;
	if (Red == colr)
		this->inside = false;
	else 
		this->inside = true;

	this->Draw(false);
}

void Ghost::Move (char maze[MAZE_ROWS][MAZE_COLS], Ghost* ghousts[], Player const * const play){
	switch (this->color){
	case Red: // CHASE
		{
			while (true){
				int muv = (rand() % 4 + 1);
				if (play->GetPowerPellet() && play->GetFrames() % 2 == 0){
					break; // slow down the ghosts
				}
				COORD newCoord;
				if (this->inside){// INSIDE - red ghost always finds the way out fast.
					COORD newCoord = CreateCoord(this->position.X, this->position.Y - 1); // W
					this->avoidMove = 2;
					TryResetSpot(maze, ghousts);
					this->SetCoord(newCoord);
					if (maze[this->position.Y][this->position.X] == MGD)
						this->inside = false;
					this->Draw(play->GetPowerPellet());
					break;
				}
				else { //OUTSIDE - follow

					short int x =  play->GetCoord().X - this->position.X; // Positive - Ghost is on player's right side
					short int y =  play->GetCoord().Y - this->position.Y; // Positive - Ghost is below player

					if (x < y){ // up or down first
						if (0 > x){ // player is upper han ghost
							newCoord = CreateCoord (this->position.X, this->position.Y - 1); // UP - W
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 4){	
								this->avoidMove = 2;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
							newCoord = CreateCoord (this->position.X - 2, this->position.Y ); // Left - A
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 1){	
								this->avoidMove = 3;
								TryResetSpot(maze, ghousts);
								COORD warpCoordL = CreateCoord(WARP_LEFT_X, WARP_Y);
								if (CoordsEqual( newCoord, warpCoordL) ){
									this->position.X = 53;
									this->position.Y = newCoord.Y;
								}
								else
									this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
							newCoord = CreateCoord (this->position.X + 2, this->position.Y ); // Right - D
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 3){	
								this->avoidMove = 1;
								TryResetSpot(maze, ghousts);
								COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
								if (CoordsEqual( newCoord, warpCoordR)){
									this->position.X = 1;
									this->position.Y = newCoord.Y;
								}
								else
									this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
							newCoord = CreateCoord (this->position.X, this->position.Y + 1); // Down - S
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 2){	
								this->avoidMove = 4;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}
						else{ // player is lower than ghost or in the same col.

							newCoord = CreateCoord (this->position.X, this->position.Y + 1); // Down - S
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 2){	
								this->avoidMove = 4;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}

							newCoord = CreateCoord (this->position.X - 2, this->position.Y ); // Left - A
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 1){	
								this->avoidMove = 3;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
							newCoord = CreateCoord (this->position.X + 2, this->position.Y ); // Right - D
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 3){	
								this->avoidMove = 1;
								TryResetSpot(maze, ghousts);
								COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
								if (CoordsEqual( newCoord, warpCoordR)){
									this->position.X = 1;
									this->position.Y = newCoord.Y;
								}
								else
									this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}

							newCoord = CreateCoord (this->position.X, this->position.Y - 1); // UP - W
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 4){	
								this->avoidMove = 2;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}
					}
					else if (y > x){ // left or right first
						newCoord = CreateCoord (this->position.X - 2, this->position.Y ); // Left - A
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 1){	
							this->avoidMove = 3;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
						newCoord = CreateCoord (this->position.X + 2, this->position.Y ); // Right - D
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 3){	
							this->avoidMove = 1;
							TryResetSpot(maze, ghousts);
							COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
							if (CoordsEqual( newCoord, warpCoordR)){
								this->position.X = 1;
								this->position.Y = newCoord.Y;
							}
							else
								this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}

						newCoord = CreateCoord (this->position.X, this->position.Y - 1); // UP - W
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 4){	
							this->avoidMove = 2;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
						newCoord = CreateCoord (this->position.X, this->position.Y + 1); // Down - S
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 2){	
							this->avoidMove = 4;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}

					else{  // x = y - random move

						if (muv == 4 && this->avoidMove != 4){ // move up W
							newCoord = CreateCoord(this->position.X, this->position.Y -1);
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
								this->avoidMove = 2;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}
						else if (muv == 1 && this->avoidMove != 1){ // move left A
							newCoord = CreateCoord(this->position.X - 2, this->position.Y );
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
								this->avoidMove = 3;
								TryResetSpot(maze, ghousts);
								COORD warpCoordL = CreateCoord(WARP_LEFT_X, WARP_Y);
								if (CoordsEqual( newCoord, warpCoordL) ){
									this->position.X = 53;
									this->position.Y = newCoord.Y;
								}

								else
									this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}

						else if (muv == 2 && this->avoidMove != 2){ // move down S
							newCoord = CreateCoord(this->position.X, this->position.Y + 1 );
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
								this->avoidMove = 4;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}
						else if (muv == 3 && this->avoidMove != 3){ // move right D
							newCoord = CreateCoord(this->position.X + 2, this->position.Y );
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
								this->avoidMove = 1;
								TryResetSpot(maze, ghousts);
								COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
								if (CoordsEqual( newCoord, warpCoordR)){
									this->position.X = 1;
									this->position.Y = newCoord.Y;
								}
								else
									this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}

					}
				}
			}
			break;
		}
	case Cyan: // Soft ambush 
		{
			int muv;
			while (true){
				if (play->GetPowerPellet() && play->GetFrames() % 2 == 0){
					break; // slow down the ghosts
				}
				COORD newCoord;
				if (this->inside){ // INSIDE
					muv = (rand() % 8 + 1);
					if (muv >= 4 && this->avoidMove != 4){ // move up W
						newCoord = CreateCoord(this->position.X, this->position.Y -1);
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR ){	
							this->avoidMove = 2;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							if (maze[this->position.Y][this->position.X] == MGD)
								this->inside = false;
							this->Draw(play->GetPowerPellet());
							break;
						}
					}
					else if (muv == 1 && this->avoidMove != 1){ // move left A
						newCoord = CreateCoord(this->position.X - 2, this->position.Y );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR ){	
							this->avoidMove = 3;
							TryResetSpot(maze, ghousts);
							TryResetSpot(maze, ghousts);
							COORD warpCoordL = CreateCoord(WARP_LEFT_X, WARP_Y);
							if (CoordsEqual( newCoord, warpCoordL) ){
								this->position.X = 53;
								this->position.Y = newCoord.Y;
							}

							else
								this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}

					else if (muv == 2 && this->avoidMove != 2){ // move down S
						newCoord = CreateCoord(this->position.X, this->position.Y + 1 );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR ){	
							this->avoidMove = 4;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}

					}

					else if (muv == 3 && this->avoidMove != 3){ // move right D
						newCoord = CreateCoord(this->position.X + 2, this->position.Y );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR ){	
							this->avoidMove = 1;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}
				}
				else{ //OUTSIDE

					muv = (rand() % 4 + 1);
					if (muv == 4 && this->avoidMove != 4){ // move up W
						newCoord = CreateCoord(this->position.X, this->position.Y -1);
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
							this->avoidMove = 2;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}
					else if (muv == 1 && this->avoidMove != 1){ // move left A
						newCoord = CreateCoord(this->position.X - 2, this->position.Y );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
							this->avoidMove = 3;
							TryResetSpot(maze, ghousts);
							COORD warpCoordL = CreateCoord(WARP_LEFT_X, WARP_Y);
							if (CoordsEqual( newCoord, warpCoordL) ){
								this->position.X = 53;
								this->position.Y = newCoord.Y;
							}
							else
								this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}

					else if (muv == 2 && this->avoidMove != 2){ // move down S
						newCoord = CreateCoord(this->position.X, this->position.Y + 1 );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
							this->avoidMove = 4;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}

					}

					else if (muv == 3 && this->avoidMove != 3){ // move right D
						newCoord = CreateCoord(this->position.X + 2, this->position.Y );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
							this->avoidMove = 1;
							TryResetSpot(maze, ghousts);
							COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
							if (CoordsEqual( newCoord, warpCoordR)){
								this->position.X = 1;
								this->position.Y = newCoord.Y;
							}
							else
								this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}

				}

			}
			break;
		}
	case Magenta: // Ambush calculate next move 
		{
			while (true){
				int muv = (rand() % 4 + 1);
				if (play->GetPowerPellet() && play->GetFrames() % 2 == 0){
					break; // slow down the ghosts
				}
				COORD newCoord;
				if (this->inside){// INSIDE - red ghost always finds the way out fast.
					COORD newCoord = CreateCoord(this->position.X, this->position.Y - 1); // W
					this->avoidMove = 2;
					TryResetSpot(maze, ghousts);
					this->SetCoord(newCoord);
					if (maze[this->position.Y][this->position.X] == MGD)
						this->inside = false;
					this->Draw(play->GetPowerPellet());
					break;
				}
				else { //OUTSIDE - follow

					short int x =  play->GetCoord().X - this->position.X; // Positive - Ghost is on player's right side
					short int y =  play->GetCoord().Y - this->position.Y; // Positive - Ghost is below player

					if (x < y){ // up or down first
						if (0 > x){ // player is upper han ghost
							newCoord = CreateCoord (this->position.X, this->position.Y - 1); // UP - W
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 4){	
								this->avoidMove = 2;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
							newCoord = CreateCoord (this->position.X - 2, this->position.Y ); // Left - A
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 1){	
								this->avoidMove = 3;
								TryResetSpot(maze, ghousts);
								COORD warpCoordL = CreateCoord(WARP_LEFT_X, WARP_Y);
								if (CoordsEqual( newCoord, warpCoordL) ){
									this->position.X = 53;
									this->position.Y = newCoord.Y;
								}
								else
									this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
							newCoord = CreateCoord (this->position.X + 2, this->position.Y ); // Right - D
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 3){	
								this->avoidMove = 1;
								TryResetSpot(maze, ghousts);
								COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
								if (CoordsEqual( newCoord, warpCoordR)){
									this->position.X = 1;
									this->position.Y = newCoord.Y;
								}
								else
									this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
							newCoord = CreateCoord (this->position.X, this->position.Y + 1); // Down - S
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 2){	
								this->avoidMove = 4;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}
						else{ // player is lower than ghost or in the same col.

							newCoord = CreateCoord (this->position.X, this->position.Y + 1); // Down - S
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 2){	
								this->avoidMove = 4;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}

							newCoord = CreateCoord (this->position.X - 2, this->position.Y ); // Left - A
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 1){	
								this->avoidMove = 3;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
							newCoord = CreateCoord (this->position.X + 2, this->position.Y ); // Right - D
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 3){	
								this->avoidMove = 1;
								TryResetSpot(maze, ghousts);
								COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
								if (CoordsEqual( newCoord, warpCoordR)){
									this->position.X = 1;
									this->position.Y = newCoord.Y;
								}
								else
									this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}

							newCoord = CreateCoord (this->position.X, this->position.Y - 1); // UP - W
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 4){	
								this->avoidMove = 2;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}
					}
					else if (y > x){ // left or right first
						newCoord = CreateCoord (this->position.X - 2, this->position.Y ); // Left - A
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 1){	
							this->avoidMove = 3;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
						newCoord = CreateCoord (this->position.X + 2, this->position.Y ); // Right - D
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 3){	
							this->avoidMove = 1;
							TryResetSpot(maze, ghousts);
							COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
							if (CoordsEqual( newCoord, warpCoordR)){
								this->position.X = 1;
								this->position.Y = newCoord.Y;
							}
							else
								this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}

						newCoord = CreateCoord (this->position.X, this->position.Y - 1); // UP - W
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 4){	
							this->avoidMove = 2;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
						newCoord = CreateCoord (this->position.X, this->position.Y + 1); // Down - S
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD && this->avoidMove != 2){	
							this->avoidMove = 4;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}

					else{  // x = y - random move

						if (muv == 4 && this->avoidMove != 4){ // move up W
							newCoord = CreateCoord(this->position.X, this->position.Y -1);
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
								this->avoidMove = 2;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}
						else if (muv == 1 && this->avoidMove != 1){ // move left A
							newCoord = CreateCoord(this->position.X - 2, this->position.Y );
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
								this->avoidMove = 3;
								TryResetSpot(maze, ghousts);
								COORD warpCoordL = CreateCoord(WARP_LEFT_X, WARP_Y);
								if (CoordsEqual( newCoord, warpCoordL) ){
									this->position.X = 53;
									this->position.Y = newCoord.Y;
								}

								else
									this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}

						else if (muv == 2 && this->avoidMove != 2){ // move down S
							newCoord = CreateCoord(this->position.X, this->position.Y + 1 );
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
								this->avoidMove = 4;
								TryResetSpot(maze, ghousts);
								this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}
						else if (muv == 3 && this->avoidMove != 3){ // move right D
							newCoord = CreateCoord(this->position.X + 2, this->position.Y );
							if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
								this->avoidMove = 1;
								TryResetSpot(maze, ghousts);
								COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
								if (CoordsEqual( newCoord, warpCoordR)){
									this->position.X = 1;
									this->position.Y = newCoord.Y;
								}
								else
									this->SetCoord(newCoord);
								this->Draw(play->GetPowerPellet());
								break;
							}
						}

					}
				}
			}
			break;
		}
	case DarkYellow: //random move
		{
			int muv;
			while (true){
				if (play->GetPowerPellet() && play->GetFrames() % 2 == 0){
					break; // slow down the ghosts
				}
				COORD newCoord;
				if (this->inside){ // INSIDE
					muv = (rand() % 8 + 1);
					if (muv >= 4 && this->avoidMove != 4){ // move up W
						newCoord = CreateCoord(this->position.X, this->position.Y -1);
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR ){	
							this->avoidMove = 2;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							if (maze[this->position.Y][this->position.X] == MGD)
								this->inside = false;
							this->Draw(play->GetPowerPellet());
							break;
						}
					}
					else if (muv == 1 && this->avoidMove != 1){ // move left A
						newCoord = CreateCoord(this->position.X - 2, this->position.Y );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR ){	
							this->avoidMove = 3;
							TryResetSpot(maze, ghousts);
							TryResetSpot(maze, ghousts);
							COORD warpCoordL = CreateCoord(WARP_LEFT_X, WARP_Y);
							if (CoordsEqual( newCoord, warpCoordL) ){
								this->position.X = 53;
								this->position.Y = newCoord.Y;
							}

							else
								this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}

					else if (muv == 2 && this->avoidMove != 2){ // move down S
						newCoord = CreateCoord(this->position.X, this->position.Y + 1 );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR ){	
							this->avoidMove = 4;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}

					}

					else if (muv == 3 && this->avoidMove != 3){ // move right D
						newCoord = CreateCoord(this->position.X + 2, this->position.Y );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR ){	
							this->avoidMove = 1;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}
				}
				else{ //OUTSIDE

					muv = (rand() % 4 + 1);
					if (muv == 4 && this->avoidMove != 4){ // move up W
						newCoord = CreateCoord(this->position.X, this->position.Y -1);
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
							this->avoidMove = 2;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}
					else if (muv == 1 && this->avoidMove != 1){ // move left A
						newCoord = CreateCoord(this->position.X - 2, this->position.Y );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
							this->avoidMove = 3;
							TryResetSpot(maze, ghousts);
							COORD warpCoordL = CreateCoord(WARP_LEFT_X, WARP_Y);
							if (CoordsEqual( newCoord, warpCoordL) ){
								this->position.X = 53;
								this->position.Y = newCoord.Y;
							}
							else
								this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}

					else if (muv == 2 && this->avoidMove != 2){ // move down S
						newCoord = CreateCoord(this->position.X, this->position.Y + 1 );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
							this->avoidMove = 4;
							TryResetSpot(maze, ghousts);
							this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}

					}

					else if (muv == 3 && this->avoidMove != 3){ // move right D
						newCoord = CreateCoord(this->position.X + 2, this->position.Y );
						if ( maze[newCoord.Y][newCoord.X] != MTL  && maze[newCoord.Y][newCoord.X] != MTR && maze[newCoord.Y][newCoord.X]  != MBL && maze[newCoord.Y][newCoord.X]  != MBR && maze[newCoord.Y][newCoord.X] != MUD && maze[newCoord.Y][newCoord.X]  != MLR && maze[newCoord.Y][newCoord.X]  != MGD ){	
							this->avoidMove = 1;
							TryResetSpot(maze, ghousts);
							COORD warpCoordR = CreateCoord(WARP_RIGHT_X, WARP_Y);
							if (CoordsEqual( newCoord, warpCoordR)){
								this->position.X = 1;
								this->position.Y = newCoord.Y;
							}
							else
								this->SetCoord(newCoord);
							this->Draw(play->GetPowerPellet());
							break;
						}
					}

				}

			}
			break;
		}
	}
}


void Ghost::Draw (bool scare){
	if (scare){
		Console::SetCursorPosition((int)this->position.X, (int)this->position.Y);
		if (Blue == this->scared){
			this->scared = White;
			Console::ForegroundColor(White);
		}
		else{
			this->scared = Blue;
			Console::ForegroundColor(Blue);
		}
		cout<<MGH;
		Console::ResetColor();
	}
	else{
		Console::SetCursorPosition((int)this->position.X, (int)this->position.Y);
		Console::ForegroundColor(this->color);
		cout<<MGH;
		Console::ResetColor();
	}
}

void Ghost::TryResetSpot (char maze[MAZE_ROWS][MAZE_COLS], Ghost const * const ghousts[]){
	bool same = false;
	for (int i = 0; i<NUM_GHOSTS; i++){
		if (this->color != ghousts[i]->color)
			if (CoordsEqual(this->position, ghousts[i]->position))
				same = true;
	}
	if (!same)
		ClearSpot(maze);
}

void Ghost::ClearSpot (char maze[MAZE_ROWS][MAZE_COLS])const {
	Console::SetCursorPosition((int)this->position.X, (int)this->position.Y);
	if (maze[this->position.Y][this->position.X] == MPP){
		Console::ForegroundColor(Green);
		maze[this->position.Y][this->position.X] = MPP;
		cout<<MPP;
		Console::ResetColor();
	}
	else if (maze[this->position.Y][this->position.X] == MDOT){
		Console::ForegroundColor(White);
		maze[this->position.Y][this->position.X] = MDOT;
		cout<<MDOT;
		Console::ResetColor();
	}
	else if (maze[this->position.Y][this->position.X] == FRUIT){
		Console::ForegroundColor(DarkRed);
		maze[this->position.Y][this->position.X] = FRUIT;
		cout<<FRUIT;
		Console::ResetColor();
	}
	else if (maze[this->position.Y][this->position.X] == MGD){
		Console::ForegroundColor(White);
		maze[this->position.Y][this->position.X] = MGD;
		cout<<MGD;
		Console::ResetColor();
	}
	else if (maze[this->position.Y][this->position.X] == PAC){
		Console::ForegroundColor(Yellow);
		Console::ResetColor();
	}
	else{
		maze[this->position.Y][this->position.X] = ' ';
		cout<< ' ';
	}

}

void Ghost::Kill (char maze[MAZE_ROWS][MAZE_COLS]){
	ClearSpot(maze);
	COORD restart = CreateCoord(27, 14);
	this->SetCoord(restart);
	Draw(true); 
	this->inside = true;
	this->avoidMove = -1;
}

void Ghost::Reset (char maze[MAZE_ROWS][MAZE_COLS], COORD const restart){
	this->avoidMove = -1;
	if (Red == this->color)
		this->inside = false;
	else 
		this->inside = true;
	ClearSpot(maze);
	SetCoord(restart);
}

void Ghost::SetCoord (const COORD pos){
	this->position.X = pos.X;
	this->position.Y = pos.Y;
}

