//
// Created by mateo on 30.11.19.
//

#include "PlayerShip.h"
#include "PlayerShipView.h"

PlayerShip::PlayerShip(const double &x, const double &y)
: Entity(std::make_pair(x,y)) {
    std::shared_ptr<ObserverPattern::Observer> newObserver = std::make_shared<PlayerShipView>();
    addObserver(newObserver);
    notify(*this, "constructor");
}

void PlayerShip::moveLeft() {
    std::pair<double, double> newCoords = getCoords();
    newCoords.first -= 1;
    setCoords(newCoords);
    notify(*this, "moveLeft");
}

void PlayerShip::moveRight() {
    std::pair<double, double> newCoords = getCoords();
    newCoords.first += 1;
    setCoords(newCoords);
    notify(*this, "moveRight");
}
