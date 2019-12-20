//
// Created by mateo on 30.11.19.
//

#include "PlayerShip.h"
#include "PlayerShipView.h"

PlayerShip::PlayerShip(const double &x, const double &y)
: Entity(std::make_pair(x,y)) {

}

void PlayerShip::moveLeft() {
    if (getCoords().first > -4) {
        std::pair<double, double> newCoords = getCoords();
        newCoords.first -= 0.1;
        setCoords(newCoords);
        notify(*this, "moveLeft");
    }
}

void PlayerShip::moveRight() {
    if (getCoords().first < 4) {
        std::pair<double, double> newCoords = getCoords();
        newCoords.first += 0.1;
        setCoords(newCoords);
        notify(*this, "moveRight");
    }
}
