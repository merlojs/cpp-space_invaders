#include "ScoreBoard.h"


ScoreBoard::ScoreBoard(ALLEGRO_FONT *font)
{	
	this->font = font;	
	this->points = 0;
	this->playerLives = 3;
}


ScoreBoard::~ScoreBoard()
{
}


void ScoreBoard::addPoints(int points) {
	this->points += points;
	//cout << "+ " << points << " points! New score: " << this->points << endl;
	this->draw();
}

void ScoreBoard::draw() {

	string scoreString = "Score: ";
	scoreString = scoreString + std::to_string(this->points);
	const char * score = scoreString.c_str();

	string livesString = "Lives: ";

	livesString = livesString + std::to_string(this->playerLives);

	const char * lives = livesString.c_str();
	
	al_draw_text(font, al_color_name("white"), 130, 125, ALLEGRO_ALIGN_CENTRE, lives);

	al_draw_text(font, al_color_name("white") , 470, 125, ALLEGRO_ALIGN_CENTRE, score);

}

int ScoreBoard::getLives() {
	return this->playerLives;
}

void ScoreBoard::removeLives(int livesToRemove) {
	this->playerLives -= livesToRemove;
}