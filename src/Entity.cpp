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

Entity::~Entity() {

}


