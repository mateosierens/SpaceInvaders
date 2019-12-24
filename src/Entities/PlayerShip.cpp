//
// Created by mateo on 30.11.19.
//

#include "PlayerShip.h"
#include "../Views/PlayerShipView.h"

PlayerShip::PlayerShip(const double &x, const double &y)
: Entity(std::make_pair(x,y)) {

}

void PlayerShip::moveLeft() {
    // do check if left side of entity reaches the side of the window, if not do move
    if (getCoords().first - (getEntityWidth()/2) > -4) {
        std::pair<double, double> newCoords = getCoords();
        newCoords.first -= 0.005;
        setCoords(newCoords);
        notify(*this, "moveLeft");
    }
}

void PlayerShip::moveRight() {
    // do check if right side of entity reaches the side of the window, if not do move
    if (getCoords().first + (getEntityWidth()/2) < 4) {
        std::pair<double, double> newCoords = getCoords();
        newCoords.first += 0.005;
        setCoords(newCoords);
        notify(*this, "moveRight");
    }

}

const std::shared_ptr<BulletController> &PlayerShip::getBullet() const {
    return bullet;
}

void PlayerShip::setBullet(const std::shared_ptr<BulletController> &bullet) {
    PlayerShip::bullet = bullet;
}
