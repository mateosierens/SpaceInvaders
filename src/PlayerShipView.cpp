//
// Created by mateo on 09.12.19.
//

#include "PlayerShipView.h"
#include "Transformation.h"

PlayerShipView::~PlayerShipView() {

}

void PlayerShipView::onNotify(const Entity &entity, std::string event) {
    if (event == "constructor") {
        sf::Texture texture;
        texture.loadFromFile("playerShip.png");
        playerSprite.setTexture(texture);
        std::pair<double, double> windowCoords = Transformation::instance().transform(0, 0);
        playerSprite.setPosition(windowCoords.first, windowCoords.second);
    }
}


