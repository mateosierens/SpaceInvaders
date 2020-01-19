//
// Created by mateo on 30.11.19.
//

#include "Entity.h"

namespace Entities {
const std::pair<float, float>& Entity::getCoords() const { return coords; }

void Entity::setCoords(const std::pair<float, float>& coords) { Entity::coords = coords; }

Entity::Entity(const std::pair<float, float>& coords) : coords(coords) {}

Entity::Entity() = default;

Entity::~Entity() = default;

float Entity::getEntityWidth() const { return entityWidth; }

void Entity::setEntityWidth(float entityWidth) { Entity::entityWidth = entityWidth; }

float Entity::getEntityHeight() const { return entityHeight; }

void Entity::setEntityHeight(float entityHeight) { Entity::entityHeight = entityHeight; }

bool Entity::collision(std::shared_ptr<Entity> otherEntity)
{
        // compute bullet bounds
        float bulletLeft = otherEntity->getCoords().first - otherEntity->getEntityWidth() / 2;
        float bulletRight = otherEntity->getCoords().first + otherEntity->getEntityWidth() / 2;
        float bulletBottom = otherEntity->getCoords().second - otherEntity->getEntityHeight() / 2;
        float bulletTop = otherEntity->getCoords().second + otherEntity->getEntityHeight() / 2;

        // compute enemy bounds
        float entityLeft = this->coords.first - this->entityWidth / 2;
        float entityRight = this->coords.first + this->entityWidth / 2;
        float entityBottom = this->coords.second - this->entityHeight / 2;
        float entityTop = this->coords.second + this->entityHeight / 2;

        // now check if any of the 4 corners of bullet is colliding with the enemy

        // left top corner
        if (bulletLeft > entityLeft && bulletLeft < entityRight && bulletTop > entityBottom && bulletTop < entityTop)
                return true;

        // right top corner
        if (bulletRight > entityLeft && bulletRight < entityRight && bulletTop > entityBottom && bulletTop < entityTop)
                return true;

        // left bottom corner
        if (bulletLeft > entityLeft && bulletLeft < entityRight && bulletBottom > entityBottom &&
            bulletBottom < entityTop)
                return true;

        // right bottom corner
        if (bulletRight > entityLeft && bulletRight < entityRight && bulletBottom > entityBottom &&
            bulletBottom < entityTop)
                return true;

        // if no if statement is true then return false, cause no collision
        return false;
}
} // namespace Entities
