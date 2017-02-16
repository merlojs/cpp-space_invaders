#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "header.h"

#include "ScoreBoard.h"
#include "Bullet.h"
#include "EnemyGrid.h"

class BulletManager
{
private:
	Bullet *playerBullet;
	vector<Bullet *> *enemyBullets;

	int framesSinceLastShot;
	void shoot(EnemyGrid *enemyGrid);
public:
	BulletManager();
	~BulletManager();

	void addPlayerBullet(Bullet *bullet);
	void addEnemyBullet(Bullet *bullet);

	bool hasPlayerBullet();
	Bullet *getPlayerBullet();

	void checkPlayerBulletCollisions(EnemyGrid *enemyGrid, ScoreBoard *scoreBoard);
	bool checkEnemyBulletCollisions(Character *playerCharacter, ScoreBoard *scoreBoard);
	void updateBulletsPosition();

	void shotGenerator(EnemyGrid * enemyGrid);
	void clearBullets();

	void draw();
};

#endif // BULLET_MANAGER_H