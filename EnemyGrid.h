#ifndef ENEMY_GRID_H
#define ENEMY_GRID_H

#include "header.h"
#include "EnemyCharacter.h"

class EnemyGrid {
	private:
		Point pos;
		Bounds bounds;
		Bounds enemyCount;
		vector<vector<EnemyCharacter *> *> *enemies;

		int remainingEnemies;
		int direction;
		int prevDirection;
		int framesSinceLastStep;
		int framesSinceLastShot;

	public:
		EnemyGrid(int width, int height, ALLEGRO_BITMAP *enemySprite, ALLEGRO_BITMAP *bulletSprite);
		~EnemyGrid();

		vector<vector<EnemyCharacter *> *> *getEnemies();

		void updatePosition();
		void resetEnemyPositions();
		void recalculateHeight();
		void enemyKilled();

		int getRemainingEnemies();
		Point getPos();
		Bounds getBounds();

		void draw();
		void debugDraw();
		EnemyCharacter *EnemyGrid::getShooter();
};

#endif // ENEMY_GRID_H