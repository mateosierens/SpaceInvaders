//
// Created by mateo on 30.11.19.
//

#include "Entity.h"

namespace Entities {
    const std::pair<double, double> &Entity::getCoords() const {
        return coords;
    }

    void Entity::setCoords(const std::pair<double, double> &coords) {
        Entity::coords = coords;
    }

    Entity::Entity(const std::pair<double, double> &coords) : coords(coords) {}

    Entity::Entity() {}

    Entity::~Entity() {}

    double Entity::getEntityWidth() const {
        return entityWidth;
    }

    void Entity::setEntityWidth(double entityWidth) {
        Entity::entityWidth = entityWidth;
    }

    double Entity::getEntityHeight() const {
        return entityHeight;
    }

    void Entity::setEntityHeight(double entityHeight) {
        Entity::entityHeight = entityHeight;
    }

    bool Entity::collision(std::shared_ptr<Entity> otherEntity) {
        // compute bullet bounds
        double bulletLeft = otherEntity->getCoords().first - otherEntity->getEntityWidth()/2;
        double bulletRight = otherEntity->getCoords().first + otherEntity->getEntityWidth()/2;
        double bulletBottom = otherEntity->getCoords().second - otherEntity->getEntityHeight()/2;
        double bulletTop = otherEntity->getCoords().second + otherEntity->getEntityHeight()/2;

        // compute enemy bounds
        double entityLeft = this->coords.first - this->entityWidth/2;
        double entityRight = this->coords.first + this->entityWidth/2;
        double entityBottom = this->coords.second - this->entityHeight/2;
        double entityTop = this->coords.second + this->entityHeight/2;

        // now check if any of the 4 corners of bullet is colliding with the enemy

        // left top corner
        if (bulletLeft > entityLeft && bulletLeft < entityRight
            && bulletTop > entityBottom && bulletTop < entityTop) return true;

        // right top corner
        if (bulletRight > entityLeft && bulletRight < entityRight
            && bulletTop > entityBottom && bulletTop < entityTop) return true;

        // left bottom corner
        if (bulletLeft > entityLeft && bulletLeft < entityRight
            && bulletBottom > entityBottom && bulletBottom < entityTop) return true;

        // right bottom corner
        if (bulletRight > entityLeft && bulletRight < entityRight
            && bulletBottom > entityBottom && bulletBottom < entityTop) return true;

        // if no if statement is true then return false, cause no collision
        return false;
    }
}




