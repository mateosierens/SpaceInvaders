//
// Created by mateo on 30.11.19.
//

#include "Bullet.h"

Bullet::Bullet(const double &x, const double &y) : Entity(std::make_pair(x,y)) {}

void Bullet::update() {
    std::pair<double, double> newCoords = getCoords();
    newCoords.second += 0.01;
    setCoords(newCoords);
    notify(*this, "updateBullet");
}

Bullet::~Bullet() {

}
