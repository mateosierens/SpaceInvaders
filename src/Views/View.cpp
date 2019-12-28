//
// Created by mateo on 09.12.19.
//

#include "View.h"
#include "../Entities/PlayerShip.h"

View::View(std::shared_ptr<Entity> &entity, const std::string &textureFile) : entity(entity) {
    // create entity on window

    // first load texture of playerSprite from file
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);

    // calculate and set middle of sprite
    double spriteWidth = sprite.getGlobalBounds().width;
    double spriteHeight = sprite.getGlobalBounds().height;
    sprite.setOrigin(spriteWidth/2, spriteHeight/2);

    // give entity knowledge of width and height of sprite in game coordinates
    entity->setEntityWidth(Transformation::instance().toGameCoordsX(spriteWidth)-Transformation::instance().toGameCoordsX(0));
    entity->setEntityHeight(Transformation::instance().toGameCoordsY(0)-Transformation::instance().toGameCoordsY(spriteHeight));

    // convert coords to window coords and set the sprite position
    std::pair<double, double> windowCoords = Transformation::instance().transform(entity.get()->getCoords().first,
                                                                                  entity.get()->getCoords().second);
    sprite.setPosition(windowCoords.first, windowCoords.second);
}

void View::makeThisObserver(std::shared_ptr<Entity> &entity) {
    // make entity observable and add this observer to its list of observers
    entity.get()->addObserver(shared_from_this());
}

const sf::Sprite &View::getSprite() const {
    return sprite;
}

void View::setSprite(const sf::Sprite &sprite) {
    View::sprite = sprite;
}

bool View::isDeleted() const {
    return deleted;
}

void View::setDeleted(bool deleted) {
    View::deleted = deleted;
}
