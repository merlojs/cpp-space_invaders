#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H

#include "header.h"

class ScoreBoard
{
	private:
		int points;
public:
	ScoreBoard();
	~ScoreBoard();

	void addPoints(int points);
	void draw();
};

#endif // SCORE_BOARD_H