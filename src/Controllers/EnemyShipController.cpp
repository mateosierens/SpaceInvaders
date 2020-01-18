//
// Created by mateo on 24.12.19.
//

#include "EnemyShipController.h"
#include "../Entities/EnemyShip.h"

namespace Controllers {
    EnemyShipController::EnemyShipController(const std::shared_ptr<Entities::Entity> &entity) : Controller(entity) {}

    EnemyShipController::~EnemyShipController() {}

    void EnemyShipController::update() {
        // check for collision with playerBullet
        // we do this by checking if any of the corners of the bullet is touching the enemy
        std::shared_ptr<BulletController> bullet = getPlayerBullet();
        std::shared_ptr<Entities::EnemyShip> enemy = std::dynamic_pointer_cast<Entities::EnemyShip>(getEntity());
        if (bullet != nullptr) {
            if (!bullet->isBulletOutOfRange()) {
                if (enemy->collision(bullet->getEntity())) {
                    // remove enemy from game
                    enemy->die();
                    setEntity(nullptr);

                    //remove bullet from game
                    bullet->hitEnemyOrPlayer();
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

    bool EnemyShipController::movingLeft() {
        std::shared_ptr<Entities::EnemyShip> enemy = std::dynamic_pointer_cast<Entities::EnemyShip>(getEntity());
        return enemy->isMovingLeft();
    }

    void EnemyShipController::setMovingLeft(bool direction) {
        std::shared_ptr<Entities::EnemyShip> enemy = std::dynamic_pointer_cast<Entities::EnemyShip>(getEntity());
        enemy->setMovingLeft(direction);
    }

    void EnemyShipController::moveDown() {
        std::shared_ptr<Entities::EnemyShip> enemy = std::dynamic_pointer_cast<Entities::EnemyShip>(getEntity());
        enemy->moveDown();
    }
}


