#include "globals.h"

#ifndef FRUITS_H
#define FRUITS_H

class Fruits{

	int score;
	COORD position;
	int sleep;
	int frames;
	ConsoleColor color;
	bool visible;

	void ChangeSpot(void);
	void ClearSpot (char maze[MAZE_ROWS][MAZE_COLS]);
public:
	Fruits(void);
	void Draw(char maze[MAZE_ROWS][MAZE_COLS]);
	void Timeout (char maze[MAZE_ROWS][MAZE_COLS]);
	void Eaten(char maze[MAZE_ROWS][MAZE_COLS]);

	const COORD GetCoord () const { return position; }
	const int GetScore() const { return score; }
	const int GetFrames() const { return frames; }
	const int GetSleep() const { return sleep; }
	const int GetVisible() const { return visible; }

	void SetCoord (const COORD pos);
	void SetFrames (const int fram );
	void SetSleep (const int slep );
	void SetVisible( const bool visi);
};

#endif