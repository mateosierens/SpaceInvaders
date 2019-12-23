//
// Created by mateo on 09.12.19.
//

#include "PlayerShipView.h"
#include "../Entities/PlayerShip.h"

PlayerShipView::~PlayerShipView() {

}

void PlayerShipView::onNotify(const Entity &entity, std::string event) {
    if (event == "moveLeft" || event == "moveRight") {
        // move sprite
        sf::Sprite playerShip = getSprite();

        // set new player position on window
        std::pair<double, double> windowCoords = Transformation::instance().transform(entity.getCoords().first,
                                                                                      entity.getCoords().second);
        playerShip.setPosition(windowCoords.first, windowCoords.second);
        setSprite(playerShip);
    }
}

PlayerShipView::PlayerShipView(std::shared_ptr<Entity> &entity, const std::string &textureFile) : View(entity,
                                                                                                       textureFile) {}


