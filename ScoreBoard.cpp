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
}

void ScoreBoard::draw() {
	
}