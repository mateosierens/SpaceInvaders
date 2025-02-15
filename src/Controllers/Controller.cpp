//
// Created by mateo on 09.12.19.
//

#include "Controller.h"

namespace Controllers {
Controller::Controller(const std::shared_ptr<Entities::Entity>& entity) : entity(entity) {}

const std::shared_ptr<Entities::Entity>& Controller::getEntity() const { return entity; }

std::pair<float, float> Controller::getCoords() { return entity->getCoords(); }

double Controller::getEntityWidth() { return entity->getEntityWidth(); }

double Controller::getEntityHeight() { return entity->getEntityHeight(); }

Controller::~Controller() = default;

void Controller::setEntity(const std::shared_ptr<Entities::Entity>& entity) { Controller::entity = entity; }
} // namespace Controllers
