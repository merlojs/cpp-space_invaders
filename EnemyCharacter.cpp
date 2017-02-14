#include "EnemyCharacter.h"
#include <iostream>

using namespace std;

EnemyCharacter::EnemyCharacter(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds dimensions) :
	Character(sprite, startingPos, dimensions) {
}

EnemyCharacter::~EnemyCharacter() {

}
