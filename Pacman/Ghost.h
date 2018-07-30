#ifndef GHOST_H
#define GHOST_H

#include <windows.h>
#include "globals.h"
#include "Player.h"


class Ghost
{
	COORD position;
	ConsoleColor color;
	ConsoleColor scared;
	int avoidMove;
	bool inside;

	void TryResetSpot (char maze[MAZE_ROWS][MAZE_COLS], Ghost const * const  ghousts[]);
	void ClearSpot (char maze[MAZE_ROWS][MAZE_COLS]) const;
public:
	Ghost(void);
	Ghost(ConsoleColor colr, COORD posi);

	void Move (char maze[MAZE_ROWS][MAZE_COLS], Ghost* ghousts[], Player const * const play);
	void Draw (bool scare);
	void Kill (char maze[MAZE_ROWS][MAZE_COLS]);
	void Reset (char maze[MAZE_ROWS][MAZE_COLS], COORD const restart);

	
	const COORD GetCoord () const { return position; }

	void SetCoord (const COORD pos);
};

#endif