#include "BulletManager.h"


BulletManager::BulletManager()
{
	this->enemyBullets = new vector < Bullet * > ;
	this->framesSinceLastShot = 0;
	this->playerBullet = 0;
}


BulletManager::~BulletManager()
{
}

void BulletManager::addPlayerBullet(Bullet *bullet)
{
	this->playerBullet = bullet;
}

void BulletManager::addEnemyBullet(Bullet *bullet)
{
	this->enemyBullets->push_back(bullet);
}

bool BulletManager::hasPlayerBullet() {
	return (this->playerBullet != 0 ? true : false);
}

void BulletManager::updateBulletsPosition()
{
	if (this->hasPlayerBullet()) {
		this->playerBullet->updatePosition();
		if (this->playerBullet->getPos().y < SCREEN_TOP) {
			this->playerBullet = 0;
		}
	}

	// Movimiento de balas de enemigos
	for (vector<Bullet *>::iterator it = this->enemyBullets->begin(); it != this->enemyBullets->end(); it++) {
		(*it)->updatePosition();
		if ((*it)->getPos().y > SCREEN_BOTTOM - 15) {
			this->enemyBullets->erase(it);
			break;
		}
	}
}

void BulletManager::draw() {
	if (this->hasPlayerBullet()) {
		this->playerBullet->draw();
	}
	
	// Dibujado de balas de enemigos
	for (vector<Bullet *>::iterator it = this->enemyBullets->begin(); it != this->enemyBullets->end(); it++) {
		(*it)->draw();
	}
}

Bullet *BulletManager::getPlayerBullet() {
	return this->playerBullet;
}


void BulletManager::clearBullets() {
	this->enemyBullets->clear();
	this->playerBullet = 0;
}

void BulletManager::checkPlayerBulletCollisions(EnemyGrid *enemyGrid, ScoreBoard *scoreBoard) {
	if (this->playerBullet) {
		for (vector<vector<EnemyCharacter *> *>::iterator it = enemyGrid->getEnemies()->begin(); it != enemyGrid->getEnemies()->end(); it++) {
			vector<EnemyCharacter *> *enemyRow = (*it);

			for (vector<EnemyCharacter *>::iterator it2 = enemyRow->begin(); it2 != enemyRow->end(); it2++) {
				if ((*it2)->isAlive() && (*it2)->isColliding(this->playerBullet)) {
					(*it2)->kill();
					// TODO: Animar explosion y esas cosas
					(*it2)->explode(); // hay que ver como se le pasa la explosion para que finalmente desaparezca
					//dependiendo si son enemigos o naves
					// lo mismo quiza funciona para animar los bichos

					scoreBoard->addPoints((*it2)->getKillScore());
					this->playerBullet = 0;
					return;
				}
			}
		}

		// Chequeo colisiones contra otras balas
		for (vector<Bullet *>::iterator it = this->enemyBullets->begin(); it != this->enemyBullets->end(); it++) {
			if (this->playerBullet->isColliding((*it))) {
				this->enemyBullets->erase(it);
				this->playerBullet = 0;
				break;
			}
		}
	}
}

void BulletManager::shotGenerator(EnemyGrid * enemyGrid) {
	this->framesSinceLastShot++;

	// Pone tope para que no puedan haber tantos disparos en un momento dado
	if (this->enemyBullets->size() < MAX_BULLET_COUNT) {

		if (this->framesSinceLastShot > MAX_FRAMES_SINCE_LAST_SHOT) {
			this->shoot(enemyGrid);
		}
		else if (this->framesSinceLastShot > MIN_FRAMES_SINCE_LAST_SHOT) {
			if (this->framesSinceLastShot % TICS_PER_SHOT_CHANCE == 0) {
				srand(time(NULL));
				if ((int)rand() % 2) {
					this->shoot(enemyGrid);
				}
			}
		}
		
	}

}

void BulletManager::shoot(EnemyGrid *enemyGrid) {
	// Asigna un enemigo para que dispare y genera el disparo
	this->addEnemyBullet(enemyGrid->getShooter()->shoot());
	framesSinceLastShot = 0;
}

bool BulletManager::checkEnemyBulletCollisions(Character *playerCharacter, ScoreBoard *scoreBoard) {
	for (vector<Bullet *>::iterator it = this->enemyBullets->begin(); it != this->enemyBullets->end(); it++) {
		if (playerCharacter->isColliding((*it))) {
			playerCharacter->kill();
			scoreBoard->removeLives(1);
			this->enemyBullets->erase(it);
			return true;
		}
	}

	return false;
}