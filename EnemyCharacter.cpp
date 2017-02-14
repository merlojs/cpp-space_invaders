#include "EnemyCharacter.h"
#include <iostream>

using namespace std;

EnemyCharacter::EnemyCharacter(ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP *bulletSprite, Point startingPos, Bounds dimensions, int killScore) :
	Character(sprite, bulletSprite, startingPos, dimensions) {
	this->shotDirection = DOWN;
	this->killScore = killScore;
}

EnemyCharacter::~EnemyCharacter() {

}

int EnemyCharacter::getKillScore() {
	return this->killScore;
}