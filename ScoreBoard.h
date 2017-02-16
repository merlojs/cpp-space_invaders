#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H

#include "header.h"

class ScoreBoard
{
private:
	int points;
	ALLEGRO_FONT *font;
	int playerLives;
public:
	ScoreBoard(ALLEGRO_FONT *font);
	~ScoreBoard();

	void addPoints(int points);
	void draw();

	void removeLives(int livesToRemove);
	int getLives();
};

#endif // SCORE_BOARD_H