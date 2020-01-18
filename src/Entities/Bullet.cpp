//
// Created by mateo on 30.11.19.
//

#include "Bullet.h"

namespace Entities {
    Bullet::Bullet(const float &x, const float &y) : Entity(std::make_pair(x,y)) {}

    void Bullet::update() {
        std::pair<float, float> newCoords = getCoords();
        if (enemy) newCoords.second -= 0.04;
        else newCoords.second += 0.04;
        setCoords(newCoords);
        notify(*this, "updateBullet");
    }

    Bullet::~Bullet() = default;

    void Bullet::removeBullet() {
        notify(*this, "remove");
    }

    void Bullet::setEnemy(bool enemy) {
        Bullet::enemy = enemy;
    }
}

