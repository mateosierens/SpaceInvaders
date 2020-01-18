//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_VIEW_H
#define SPACEINVADERS_VIEW_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Observer.h"
#include "../Transformation.h"

namespace Views {
    class View : public ObserverPattern::Observer {
    private:
        bool deleted = false;
        std::shared_ptr<Entities::Entity> entity;
        sf::Sprite sprite;
        sf::Texture texture;
    public:
        View(std::shared_ptr<Entities::Entity> &entity, const std::string &textureFile);

        ~View() override = default;

        void onNotify(const Entities::Entity &entity, std::string event) override = 0;

        virtual void makeThisObserver(std::shared_ptr<Entities::Entity> &entity);

        const sf::Sprite &getSprite() const;

        void setSprite(const sf::Sprite &sprite);

        bool isDeleted() const;

        void setDeleted(bool deleted);
    };
}

#endif //SPACEINVADERS_VIEW_H
