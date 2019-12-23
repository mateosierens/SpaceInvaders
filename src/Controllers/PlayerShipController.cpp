//
// Created by mateo on 09.12.19.
//

#include "PlayerShipController.h"
#include "../Entities/PlayerShip.h"

PlayerShipController::PlayerShipController(const std::shared_ptr<Entity> &entity) : Controller(entity) {}

void PlayerShipController::move(const char &c) {
    std::shared_ptr<PlayerShip> ship = std::dynamic_pointer_cast<PlayerShip>(getEntity());
    if (c == 'Q') ship->moveLeft();
    else if (c == 'D') ship->moveRight();
}

bool PlayerShipController::shotBullet() {
    std::shared_ptr<PlayerShip> ship = std::dynamic_pointer_cast<PlayerShip>(getEntity());
    if (ship->getBullet() == nullptr) return false;
    return true;
}

void PlayerShipController::setBullet(std::shared_ptr<BulletController> &bullet) {
    std::shared_ptr<PlayerShip> ship = std::dynamic_pointer_cast<PlayerShip>(getEntity());
    ship->setBullet(bullet);
}

void PlayerShipController::update() {
    // check if the bullet ship controlls still exists, if not we need to notify the playerShip that it can shoot
    // a bullet again
    std::shared_ptr<PlayerShip> ship = std::dynamic_pointer_cast<PlayerShip>(getEntity());
    if (ship->getBullet() != nullptr && ship->getBullet()->isBulletOutOfRange()) {
        ship->setBullet(nullptr);
    }
}

