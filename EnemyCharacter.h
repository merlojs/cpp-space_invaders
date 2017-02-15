#ifndef ENEMY_CHARACTER_H
#define ENEMY_CHARACTER_H

#include "Character.h"

class EnemyCharacter : public Character {
protected:
	int killScore;
public:
	EnemyCharacter(ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP *bulletSprite, Point startingPos, Bounds dimensions, int killScore);
	~EnemyCharacter();

	int getKillScore();
};

#endif // ENEMY_CHARACTER_H