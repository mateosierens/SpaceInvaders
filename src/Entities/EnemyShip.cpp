//
// Created by mateo on 30.11.19.
//

#include "EnemyShip.h"

EnemyShip::EnemyShip(const double &x, const double &y) : Entity(std::make_pair(x,y)) {}

void EnemyShip::moveLeft() {
    // do check if left side of entity reaches the side of the window, if not do move
    if (getCoords().first - (getEntityWidth()/2) > -4) {
        std::pair<double, double> newCoords = getCoords();
        newCoords.first -= 0.015;
        setCoords(newCoords);
        notify(*this, "moveLeftEnemy");
    }
}

void EnemyShip::moveRight() {
    // do check if right side of entity reaches the side of the window, if not do move
    if (getCoords().first + (getEntityWidth()/2) < 4) {
        std::pair<double, double> newCoords = getCoords();
        newCoords.first += 0.015;
        setCoords(newCoords);
        notify(*this, "moveRightEnemy");
    }
}

void EnemyShip::moveDown() {
    // do check if right side of entity reaches the side of the window, if not do move
    if (getCoords().second + (getEntityHeight()/2) > -3) {
        std::pair<double, double> newCoords = getCoords();
        newCoords.second -= 0.15;
        setCoords(newCoords);
        notify(*this, "moveDownEnemy");
    }
}

bool EnemyShip::isMovingLeft() const {
    return movingLeft;
}

void EnemyShip::setMovingLeft(bool movingLeft) {
    EnemyShip::movingLeft = movingLeft;
}

void EnemyShip::die() {
    notify(*this, "dead");
}
