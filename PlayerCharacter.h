#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "header.h"
#include "Character.h"

class PlayerCharacter : public Character {
	public:
	    PlayerCharacter(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds dimensions);
		~PlayerCharacter(){};

		void processInput(GameInput *playerInput);
};

#endif // PLAYER_CHARACTER_H
