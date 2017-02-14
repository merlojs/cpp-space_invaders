#ifndef ENEMY_CHARACTER_H
#define ENEMY_CHARACTER_H

#include "Character.h"

class EnemyCharacter : public Character {
public:
	EnemyCharacter(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds dimensions);
	~EnemyCharacter();

	void processInput(GameInput *playerInput);
};

#endif // ENEMY_CHARACTER_H