//
// Created by mateo on 24.12.19.
//

#include "EnemyShipController.h"
#include "../Entities/EnemyShip.h"

EnemyShipController::EnemyShipController(const std::shared_ptr<Entity> &entity) : Controller(entity) {}

EnemyShipController::~EnemyShipController() {}

// Helper function to check if bullet collides with an enemy, returns true if enemy is hit
bool bulletCollision (const std::shared_ptr<BulletController> &bullet, const std::shared_ptr<EnemyShip> &enemy) {

    // compute bullet bounds
    double bulletLeft = bullet->getCoords().first - bullet->getEntityWidth()/2;
    double bulletRight = bullet->getCoords().first + bullet->getEntityWidth()/2;
    double bulletBottom = bullet->getCoords().second - bullet->getEntityHeight()/2;
    double bulletTop = bullet->getCoords().second + bullet->getEntityHeight()/2;

    // compute enemy bounds
    double enemyLeft = enemy->getCoords().first - enemy->getEntityWidth()/2;
    double enemyRight = enemy->getCoords().first + enemy->getEntityWidth()/2;
    double enemyBottom = enemy->getCoords().second - enemy->getEntityHeight()/2;
    double enemyTop = enemy->getCoords().second + enemy->getEntityHeight()/2;

    // now check if any of the 4 corners of bullet is colliding with the enemy

    // left top corner
    if (bulletLeft > enemyLeft && bulletLeft < enemyRight
    && bulletTop > enemyBottom && bulletTop < enemyTop) return true;

    // right top corner
    if (bulletRight > enemyLeft && bulletRight < enemyRight
        && bulletTop > enemyBottom && bulletTop < enemyTop) return true;

    // left bottom corner
    if (bulletLeft > enemyLeft && bulletLeft < enemyRight
        && bulletBottom > enemyBottom && bulletBottom < enemyTop) return true;

    // right bottom corner
    if (bulletRight > enemyLeft && bulletRight < enemyRight
        && bulletBottom > enemyBottom && bulletBottom < enemyTop) return true;

    // if no if statement is true then return false, cause no collision
    return false;

}

void EnemyShipController::update() {
    // check for collision with playerBullet
    // we do this by checking if any of the corners of the bullet is touching the enemy
    std::shared_ptr<BulletController> bullet = getPlayerBullet();
    std::shared_ptr<EnemyShip> enemy = std::dynamic_pointer_cast<EnemyShip>(getEntity());
    if (bullet != nullptr) {
        if (!bullet->isBulletOutOfRange()) {
            if (bulletCollision(bullet, enemy)) {
                // remove enemy from game
                enemy->die();
                setEntity(nullptr);

                //remove bullet from game
                bullet->hitEnemy();
                bullet->setEntity(nullptr);
            } else {
                // move enemy
                if (enemy->isMovingLeft()) {
                    if (getCoords().first - (getEntityWidth()/2) < -4) {
                        // start moving right if enemy reaches left side of window
                        enemy->setMovingLeft(false);
                        enemy->moveDown();
                    } else {
                        enemy->moveLeft();
                    }
                } else {
                    if (getCoords().first + (getEntityWidth()/2) > 4) {
                        // start moving left if enemy reaches right side of window
                        enemy->setMovingLeft(true);
                        enemy->moveDown();
                    } else {
                        enemy->moveRight();
                    }
                }
            }
        } else {
            setPlayerBullet(nullptr);
        }
    } else {
        // move enemy
        if (enemy->isMovingLeft()) {
            if (getCoords().first - (getEntityWidth()/2) < -4) {
                // start moving right if enemy reaches left side of window
                enemy->setMovingLeft(false);
                enemy->moveDown();
            } else {
                enemy->moveLeft();
            }
        } else {
            if (getCoords().first + (getEntityWidth()/2) > 4) {
                // start moving left if enemy reaches right side of window
                enemy->setMovingLeft(true);
                enemy->moveDown();
            } else {
                enemy->moveRight();
            }
        }
    }

}

const std::shared_ptr<BulletController> &EnemyShipController::getPlayerBullet() const {
    return playerBullet;
}

void EnemyShipController::setPlayerBullet(const std::shared_ptr<BulletController> &playerBullet) {
    EnemyShipController::playerBullet = playerBullet;
}
