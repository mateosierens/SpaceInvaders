//
// Created by mateo on 23.12.19.
//

#include "BulletView.h"

namespace Views {
BulletView::BulletView(std::shared_ptr<Entities::Entity>& entity, const std::string& textureFile)
    : View(entity, textureFile)
{
}

BulletView::~BulletView() = default;

void BulletView::onNotify(const Entities::Entity& entity, std::string event)
{
        if (event == "updateBullet") {
                // move sprite
                sf::Sprite bullet = getSprite();

                // set new bullet position on window
                std::pair<float, float> windowCoords =
                    Transformation::instance().transform(entity.getCoords().first, entity.getCoords().second);
                bullet.setPosition(windowCoords.first, windowCoords.second);
                setSprite(bullet);
        } else if (event == "remove") {
                setDeleted(true);
        }
}
} // namespace Views
