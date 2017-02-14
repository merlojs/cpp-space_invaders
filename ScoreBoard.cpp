#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
	this->points = 0;
}


ScoreBoard::~ScoreBoard()
{
}


void ScoreBoard::addPoints(int points) {
	this->points += points;
	cout << "+ " << points << " points! New score: " << this->points << endl;
}

void ScoreBoard::draw() {
	// TODO: Implementar!!
}