// TODO Part 1: Class Declaration for Player

#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include "globals.h"
#include "Fruits.h"

class Player
{
	COORD position;
	char *name;
	int score;
	int lives;
	bool powerPellet;
	int franes;

	void Draw (char maze[MAZE_ROWS][MAZE_COLS]) const;
	void ClearSpot (char maze[MAZE_ROWS][MAZE_COLS]) const;

public:

	//Player(void);
	Player (char maze[MAZE_ROWS][MAZE_COLS], COORD const pos, char const *nme);
	~Player();

	void Move (char maze[MAZE_ROWS][MAZE_COLS], COORD const posi, Fruits *fruit);
	void const DisplayHUD (void) const;
	void Reset(char maze[MAZE_ROWS][MAZE_COLS],  COORD const pos);
	inline void Kill(void) {this->lives -= 1; }
	inline void GhostKilled (void) {this->score += 200; }
		
#pragma region Accessors and Mutators

	const COORD GetCoord () const { return position; }
	const char * const GetName() const { return name; }
	int GetScore() const { return score; }
	int GetLives() const { return lives; }
	bool GetPowerPellet () const { return powerPellet; }
	int GetFrames () const { return franes; }
 

	void SetCoord (const COORD pos);
	void SetName (const char * const n);
	void SetScore (int sco);
	void SetLives (int liv);

#pragma endregion

};

#endif