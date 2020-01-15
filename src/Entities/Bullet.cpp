//
// Created by mateo on 30.11.19.
//

#include "Bullet.h"

Bullet::Bullet(const double &x, const double &y) : Entity(std::make_pair(x,y)) {}

void Bullet::update() {
    std::pair<double, double> newCoords = getCoords();
    if (enemy) newCoords.second -= 0.005;
    else newCoords.second += 0.005;
    setCoords(newCoords);
    notify(*this, "updateBullet");
}

Bullet::~Bullet() {

}

void Bullet::removeBullet() {
    notify(*this, "remove");
}

void Bullet::setEnemy(bool enemy) {
    Bullet::enemy = enemy;
}
