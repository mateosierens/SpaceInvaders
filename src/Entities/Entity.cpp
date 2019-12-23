//
// Created by mateo on 30.11.19.
//

#include "Entity.h"

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


