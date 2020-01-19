//
// Created by mateo on 24.12.19.
//

#include "EnemyShipView.h"
#include "../Entities/EnemyShip.h"

namespace Views {
EnemyShipView::~EnemyShipView() = default;

void EnemyShipView::onNotify(const Entities::Entity& entity, std::string event)
{
        if (event == "moveLeftEnemy" || event == "moveRightEnemy" || event == "moveDownEnemy") {
                // move sprite
                sf::Sprite playerShip = getSprite();

                // set new player position on window
                std::pair<float, float> windowCoords =
                    Transformation::instance().transform(entity.getCoords().first, entity.getCoords().second);
                playerShip.setPosition(windowCoords.first, windowCoords.second);
                setSprite(playerShip);
        } else if (event == "dead") {
                // with this bool vector of views in game class knows it is not supposed to be on screen anymore
                // and it will erase this enemy from its list of views
                setDeleted(true);
        }
}

EnemyShipView::EnemyShipView(std::shared_ptr<Entities::Entity>& entity, const std::string& textureFile)
    : View(entity, textureFile)
{
}
} // namespace Views