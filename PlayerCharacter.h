#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "Character.h"
#include "BulletManager.h"

class PlayerCharacter : public Character {
	private:
		int lives;
		Point startingPos;

	public:
		PlayerCharacter(ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP *bulletSprite, Point startingPos, Bounds dimensions);
		~PlayerCharacter();

		void processInput(GameInput *playerInput, BulletManager *bulletManager);
		void resetPosition();
};

#endif // PLAYER_CHARACTER_H
