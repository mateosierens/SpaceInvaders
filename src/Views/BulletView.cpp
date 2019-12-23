//
// Created by mateo on 23.12.19.
//

#include "BulletView.h"

BulletView::BulletView(std::shared_ptr<Entity> &entity, const std::string &textureFile) : View(entity, textureFile) {

}

BulletView::~BulletView() {

}

void BulletView::onNotify(const Entity &entity, std::string event) {
    if (event == "updateBullet") {
        // move sprite
        sf::Sprite bullet = getSprite();

        // set new bullet position on window
        std::pair<double, double> windowCoords = Transformation::instance().transform(entity.getCoords().first,
                                                                                      entity.getCoords().second);
        bullet.setPosition(windowCoords.first, windowCoords.second);
        setSprite(bullet);
    }
}
