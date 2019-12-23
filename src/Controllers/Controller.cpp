//
// Created by mateo on 09.12.19.
//

#include "Controller.h"

Controller::Controller(const std::shared_ptr<Entity> &entity) : entity(entity) {}

const std::shared_ptr<Entity> &Controller::getEntity() const {
    return entity;
}

std::pair<double, double> Controller::getCoords() {
    return entity->getCoords();
}

double Controller::getEntityWidth() {
    return entity->getEntityWidth();
}

double Controller::getEntityHeight() {
    return entity->getEntityHeight();
}

Controller::~Controller() {

}

void Controller::update() {
    // base update function
}

void Controller::setEntity(const std::shared_ptr<Entity> &entity) {
    Controller::entity = entity;
}
