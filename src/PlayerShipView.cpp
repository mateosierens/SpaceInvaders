//
// Created by mateo on 09.12.19.
//

#include "PlayerShipView.h"
#include "PlayerShip.h"
#include "Transformation.h"

PlayerShipView::~PlayerShipView() {

}

void PlayerShipView::onNotify(const Entity &entity, std::string event) {
    if (event == "moveLeft" || event == "moveRight") {
        std::pair<double, double> windowCoords = Transformation::instance().transform(entity.getCoords().first,
                                                                                      entity.getCoords().second);
        playerSprite.setPosition(windowCoords.first, windowCoords.second);
    }
}

PlayerShipView::PlayerShipView(std::shared_ptr<Entity> &entity) : View(entity) {
    // create PlayerShip on window

    // first load texture of playerSprite from file
    playerTexture.loadFromFile("playerShip.png");
    playerSprite.setTexture(playerTexture);

    // calculate and set middle of sprite
    double spriteWidth = playerSprite.getGlobalBounds().width;
    double spriteHeight = playerSprite.getGlobalBounds().height;
    playerSprite.setOrigin(spriteWidth/2, spriteHeight/2);

    // convert coords to window coords and set the sprite position
    std::pair<double, double> windowCoords = Transformation::instance().transform(entity.get()->getCoords().first,
            entity.get()->getCoords().second);
    playerSprite.setPosition(windowCoords.first, windowCoords.second);
}

const sf::Sprite &PlayerShipView::getPlayerSprite() const {
    return playerSprite;
}

void PlayerShipView::makeThisObserver(std::shared_ptr<Entity> &entity) {
    // make entity observable and add this observer (PlayerShipView) to its list of observers
    entity.get()->addObserver(shared_from_this());
}


