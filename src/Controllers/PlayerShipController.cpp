//
// Created by mateo on 09.12.19.
//

#include "PlayerShipController.h"
#include "../Entities/PlayerShip.h"

namespace Controllers {
PlayerShipController::PlayerShipController(const std::shared_ptr<Entities::Entity>& entity) : Controller(entity) {}

void PlayerShipController::move(const char& c)
{
        std::shared_ptr<Entities::PlayerShip> ship = std::dynamic_pointer_cast<Entities::PlayerShip>(getEntity());
        if (c == 'Q')
                ship->moveLeft();
        else if (c == 'D')
                ship->moveRight();
}

bool PlayerShipController::shotBullet()
{
        std::shared_ptr<Entities::PlayerShip> ship = std::dynamic_pointer_cast<Entities::PlayerShip>(getEntity());
        if (ship->getBullet() == nullptr)
                return false;
        return true;
}

void PlayerShipController::setBullet(std::shared_ptr<BulletController>& bullet)
{
        std::shared_ptr<Entities::PlayerShip> ship = std::dynamic_pointer_cast<Entities::PlayerShip>(getEntity());
        ship->setBullet(bullet);
}

void PlayerShipController::update()
{
        // check if the bullet ship controlls still exists, if not we need to notify the playerShip that it can shoot
        // a bullet again
        std::shared_ptr<Entities::PlayerShip> ship = std::dynamic_pointer_cast<Entities::PlayerShip>(getEntity());
        if (ship->getBullet() != nullptr && ship->getBullet()->isBulletOutOfRange()) {
                ship->setBullet(nullptr);
        }
        for (int i = 0; i < ship->getEnemyBullets().size(); i++) {

                // if enemyBullet moves out of scope of screen, we remove it from enemyBullets
                if (ship->getEnemyBullets()[i]->getEntity() == nullptr)
                        ship->removeEnemyBullet(i);
        }
        for (const std::shared_ptr<BulletController>& enemyBullet : ship->getEnemyBullets()) {
                if (ship->collision(enemyBullet->getEntity())) {
                        ship->decreaseLives();
                        enemyBullet->hitEnemyOrPlayer();
                        enemyBullet->setEntity(nullptr);
                }
        }
}

void PlayerShipController::addEnemyBullet(const std::shared_ptr<BulletController>& enemyBullet)
{
        std::shared_ptr<Entities::PlayerShip> ship = std::dynamic_pointer_cast<Entities::PlayerShip>(getEntity());
        ship->addEnemyBullet(enemyBullet);
}

bool PlayerShipController::alive()
{
        std::shared_ptr<Entities::PlayerShip> ship = std::dynamic_pointer_cast<Entities::PlayerShip>(getEntity());
        return ship->isAlive();
}

void PlayerShipController::kill()
{
        std::shared_ptr<Entities::PlayerShip> ship = std::dynamic_pointer_cast<Entities::PlayerShip>(getEntity());
        ship->kill();
}

int PlayerShipController::getLives()
{
        std::shared_ptr<Entities::PlayerShip> ship = std::dynamic_pointer_cast<Entities::PlayerShip>(getEntity());
        return ship->getLives();
}
} // namespace Controllers
